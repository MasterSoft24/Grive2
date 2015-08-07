/*
	grive2: an GPL program to sync a local directory with Google Drive
	Forked from grive project
	
	Copyright (C) 2012  Wan Wai Ho
	Copyright (C) 2014  Vladimir Kamensky
        Copyright (C) 2015  Vitaliy Filippov

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation version 2
	of the License.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include "util/Config.hh"

#include "base/Drive.hh"
#include "drive2/Syncer2.hh"

#include "http/CurlAgent.hh"
#include "protocol/AuthAgent.hh"
#include "protocol/OAuth2.hh"
#include "json/Val.hh"

#include "bfd/Backtrace.hh"
#include "util/Exception.hh"
#include "util/log/Log.hh"
#include "util/log/CompositeLog.hh"
#include "util/log/DefaultLog.hh"
#include "drive2/Feed2.hh"

// boost header
#include <boost/exception/all.hpp>
#include <boost/program_options.hpp>

// initializing libgcrypt, must be done in executable
#include <gcrypt.h>

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

 char cCurrentPath[FILENAME_MAX];


const std::string client_id		= "502802353894-fjbma0deq577lug7hrui8ma3ogv03se2.apps.googleusercontent.com" ;
const std::string client_secret	= "HMQXlR2HDhrw58KR5lDQYKea" ;


// ===== global vars =====
 extern std::vector<std::string> exclude_file;
 extern std::string path_to_sync_dir;
 extern std::string work_dir;
 extern bool use_include;

//=======================

std::string work_dir;



using namespace gr ;
//using namespace gr::v1 ;
namespace po = boost::program_options;

// libgcrypt insist this to be done in application, not library
void InitGCrypt()
{
	if ( !gcry_check_version(GCRYPT_VERSION) )
		throw std::runtime_error( "libgcrypt version mismatch" ) ;

	// disable secure memory
	gcry_control(GCRYCTL_DISABLE_SECMEM, 0);

	// tell Libgcrypt that initialization has completed
	gcry_control(GCRYCTL_INITIALIZATION_FINISHED, 0);
}

void InitLog( const po::variables_map& vm )
{
	std::auto_ptr<log::CompositeLog> comp_log(new log::CompositeLog) ;
	LogBase* console_log = comp_log->Add( std::auto_ptr<LogBase>( new log::DefaultLog ) ) ;

	if ( vm.count( "log" ) )
	{
		std::auto_ptr<LogBase> file_log(new log::DefaultLog( vm["log"].as<std::string>() )) ;
		file_log->Enable( log::debug ) ;
		file_log->Enable( log::verbose ) ;
		file_log->Enable( log::info ) ;
		file_log->Enable( log::warning ) ;
		file_log->Enable( log::error ) ;
		file_log->Enable( log::critical ) ;
		
		// log grive version to log file
		file_log->Log( log::Fmt("Grive2 version " VERSION " " __DATE__ " " __TIME__), log::verbose ) ;
		file_log->Log( log::Fmt("current time: %1%") % DateTime::Now(), log::verbose ) ;
		
		comp_log->Add( file_log ) ;
	}
	
	if ( vm.count( "verbose" ) )
	{
		console_log->Enable( log::verbose ) ;
	}
	
	if ( vm.count( "debug" ) )
	{
		console_log->Enable( log::verbose ) ;
		console_log->Enable( log::debug ) ;
	}
	LogBase::Inst( std::auto_ptr<LogBase>(comp_log.release()) ) ;
}

//std::vector<std::string> file_ids;

std::vector<std::string> GetDriveFilenames(v2::Syncer2 syncer, gr::AuthAgent* agent){
        std::auto_ptr<gr::Feed> feed=  syncer.GetAll();
        
        bool d=feed->GetNext(agent);
        
       Entry e;
      
        std::vector<std::string> out;
        
        
        gr::Feed::iterator itf= feed->begin();
        
        for(itf;itf!=feed->end();itf++){
            e=*itf;
            std::string f=e.Title();
            Feed::iterator rs;
           
            while((rs=feed->find(e.ParentHref()))!=feed->end()){
                               f=(*rs).Title()+"/"+f;
                               e=*rs;
            }
                            out.push_back("/"+f);            
            
            //std::cout << f << "\n";
             
        }
        
        std::sort(out.begin(), out.end()); 
        
        return out;
}


int Main( int argc, char **argv )
{
    
     GetCurrentDir(cCurrentPath, sizeof(cCurrentPath));
     
     work_dir=&cCurrentPath[0];
     path_to_sync_dir=work_dir;    
    
    
	InitGCrypt() ;
	
	// construct the program options
	po::options_description desc( "Grive2  options" );
	desc.add_options()
		( "help,h",		"Produce help message" )
		( "version,v",	"Display Grive version" )
		( "auth,a",		"Request authorization token" )
		( "path,p",		po::value<std::string>(), "Path to sync")
		//( "dir,s",		po::value<std::string>(), "Subdirectory to sync")
		( "verbose,V",	"Verbose mode. Enable more messages than normal.")
		( "log-xml",	"Log more HTTP responses as XML for debugging.")
		( "new-rev",	"Create new revisions in server for updated files.")
		( "debug,d",	"Enable debug level messages. Implies -v.")
		( "log,l",		po::value<std::string>(), "Set log output filename." )
		( "force,f",	"Force grive to always download a file from Google Drive "
						"instead of uploading it." )
		( "dry-run",	"Only detect which files need to be uploaded/downloaded, "
						"without actually performing them." )
                ( "list,s",		"Produce Google drive remote file list" )
                ( "use-include",		"Use .include file instead .exclude" )
	;
	
	po::variables_map vm;
	po::store(po::parse_command_line( argc, argv, desc), vm );
	po::notify(vm);
	
	// simple commands that doesn't require log or config
	if ( vm.count("help") )
	{
		std::cout << desc << std::endl ;
		return 0 ;
	}
	else if ( vm.count( "version" ) )
	{
		std::cout
			<< "Grive2 version " << VERSION << ' ' << __DATE__ << ' ' << __TIME__ << std::endl ;
		return 0 ;
	}

	// initialize logging
	InitLog(vm) ;
	
	Config config(vm) ;
	
	Log( "config file name %1%", config.Filename(), log::verbose );

	if ( vm.count( "auth" ) )
	{
		std::cout
			<< "-----------------------\n"
			<< "Please go to this URL and get an authentication code:\n\n"
			<< OAuth2::MakeAuthURL( client_id )
			<< std::endl ;
		
		std::cout
			<< "\n-----------------------\n"
			<< "Please input the authentication code here: " << std::endl ;
		std::string code ;
		std::cin >> code ;
		
		OAuth2 token( client_id, client_secret ) ;
		token.Auth( code ) ;
		
		// save to config
		config.Set( "refresh_token", Val( token.RefreshToken() ) ) ;
		config.Save() ;
                
                std::cout << "\n\nToken was succesfully accepted and saved. To start working with the program run grive2 without any options for start full synchronize. \nFor file list setup which will be loaded, read readme.\n";
                
                return 0;
	}
	
	std::string refresh_token ;
	try
	{
		refresh_token = config.Get("refresh_token").Str() ;
	}
	catch ( Exception& e )
	{
		Log(
			"Please run grive with the \"-a\" option if this is the "
			"first time you're accessing your Google Drive!",
			log::critical ) ;
		
		return -1;
	}
	
	OAuth2 token( refresh_token, client_id, client_secret ) ;
	AuthAgent agent( token, std::auto_ptr<http::Agent>( new http::CurlAgent ) ) ;
	v2::Syncer2 syncer( &agent );
        
        //--------------------------------------
        if ( vm.count( "list" ) != 0 ){// remote files list
            
        
            std::vector<std::string> out=    GetDriveFilenames(syncer,&agent);
            
            for(std::vector<std::string>::iterator i=out.begin();i!=out.end();i++){
                //Log("%1%",*i);
                std::cout << (*i).c_str();
                std::cout << "\n";
            }
            
            return 0;
        }
        
        

        
        // read exclude config file
        
            std::string w_path;
            if(vm.count("path")==0){
                w_path=work_dir;// "."    
            }
            else{
                w_path=	vm["path"].as<std::string>();
                path_to_sync_dir=w_path;
            }
            
            
            
            
            if ( vm.count( "use-include" ) != 0 ){// use .include instead .exclude

                w_path+="/.include";
                use_include=true;
            } 
            else{
                w_path+="/.exclude";
                use_include=false;
            }
            
        

  
            std::ifstream is (w_path.c_str(), std::ios_base::in);
            std::string line;
                while (getline(is, line, '\n'))
                {
//                    int ssp=line.find("/",1);
//                    std::string rt=line.substr(0,ssp);
//                    line=line.replace(0,ssp,".");
                  exclude_file.push_back (line);
                   
                }
            
            //---------------------------------
        

	Drive drive( &syncer, config.GetAll() ) ;
	drive.DetectChanges() ;

	if ( vm.count( "dry-run" ) == 0 )
	{
		drive.Update() ;
		drive.SaveState() ;
	}
	else
		drive.DryRun() ;
	
	config.Save() ;
	Log( "Finished!", log::info ) ;
	return 0 ;
}

int main( int argc, char **argv )
{
	try
	{
		return Main( argc, argv ) ;
	}
	catch ( Exception& e )
	{
		Log( "exception: %1%", boost::diagnostic_information(e), log::critical ) ;
	}
	catch ( std::exception& e )
	{
		Log( "exception: %1%", e.what(), log::critical ) ;
	}
	catch ( ... )
	{
		Log( "unexpected exception", log::critical ) ;
	}
	return -1 ;
}
