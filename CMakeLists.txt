cmake_minimum_required(VERSION 2.8)

# Grive version. remember to update it for every new release!
set( GRIVE2_VERSION "0.1" )

# common compile options
add_definitions( -DVERSION="${GRIVE2_VERSION}" )
add_definitions( -D_FILE_OFFSET_BITS=64 )

add_subdirectory( libgrive )
add_subdirectory( grive )
