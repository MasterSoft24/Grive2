# Maintainer: Giuseppe CalГ  <jiveaxe@gmail.com>
# Contributer: giacomogiorgianni@gmail.com
# Contributor: TingPing <tingping@tingping.se>

pkgname=Grive2
pkgver=0.1
pkgrel=1
pkgdesc="Open source Linux client for Google Drive"
arch=('i686' 'x86_64')
url="http://www.lbreda.com/grive/start"
license=('GPL')
categories=('network')
#if [ "${CARCH}" = 'x86_64' ]; then
#    depends=('gcc-libs-multilib' 'lib32-curl' 'lib32-json-c' 'lib32-openssl' 'boost' 'lib32-libgcrypt' 'lib32-#expat' 'yajl')
#elif [ "${CARCH}" = 'i686' ]; then
#    depends=('gcc-libs' 'curl' 'json-c' 'openssl' 'boost-libs' 'libgcrypt' 'expat' 'yajl')
#fi

depends=('json-c' 'curl' 'boost-libs' 'expat' 'libgcrypt' 'yajl')
#makedepends=('cmake' 'cppunit' 'boost')
makedepends=('cmake' 'git' 'boost' 'yajl' 'json-c' )
options=(!emptydirs)

source=("https://github.com/MasterSoft24/Grive2/archive/v$pkgver.tar.gz")
md5sums=('87cf3ac03cd1288819aa9b38025e7837')


build() {
	cd "$srcdir/$pkgname-$pkgver"
	
  
  sed -i -e '/find_package(BFD)/d' libgrive/CMakeLists.txt 

      sed -i '9s|json/json.h|json-c/json.h|g' cmake/Modules/FindJSONC.cmake
      sed -i '10s|json|json-c json|g' cmake/Modules/FindJSONC.cmake
      sed -i '32s|json/json_tokener.h|json-c/json_tokener.h|g' libgrive/src/protocol/Json.cc
      sed -i '33s|json/linkhash.h|json-c/linkhash.h|g' libgrive/src/protocol/Json.cc
if [ "${CARCH}" = 'i686' ]; then
   sed -i '251s|m_last_sync.Sec() ) )|(boost::uint64_t)m_last_sync.Sec() ) )|g' libgrive/src/drive/State.cc
   sed -i '252s|m_last_sync.NanoSec() ) )|(boost::uint64_t)m_last_sync.NanoSec() ) )|g' libgrive/src/drive/State.cc
   sed -i '256s|m_cstamp) |(boost::uint64_t)m_cstamp) |g' libgrive/src/drive/State.cc
fi 

#rm -rf build
  #mkdir build
  #cd build
  #cmake .. -DCMAKE_BUILD_TYPE=Release \
  #  -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_EXE_LINKER_FLAGS=-ljson-c
  #sed -i '225s|libjson|libjson-c|g' CMakeCache.txt
#cd src
 make   
}
 
package() {
	cd "$srcdir/grive-$pkgver/build"
	
	make DESTDIR="$pkgdir" install
	#install -D "$srcdir/grive-$pkgver/build/grive/grive" "$pkgdir/usr/bin/grive"
	#install -d $pkgdir/usr/lib
	mkdir "${pkgdir}/usr/lib"
	ln -s "/usr/lib/libboost_program_options.so" "${pkgdir}/usr/lib/libbost_program_options.so.1.56.0"
	ln -s "/usr/lib/libboost_filesystem.so" "${pkgdir}/usr/lib/libboost_filesystem.so.1.56"
	#install -D "$srcdir/grive-master/build/grive/grive" "$pkgdir/usr/bin/grive"
}
