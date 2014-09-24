#!/bin/bash

sed -i -e '/find_package(BFD)/d' libgrive/CMakeLists.txt 
  sed -i -e '43d' bgrive/CMakeLists.txt 
      sed -i '9s|json/json.h|json-c/json.h|g' cmake/Modules/FindJSONC.cmake
      sed -i '10s|json|json-c json|g' cmake/Modules/FindJSONC.cmake
      sed -i '32s|json/json_tokener.h|json-c/json_tokener.h|g' libgrive/src/protocol/Json.cc
      sed -i '33s|json/linkhash.h|json-c/linkhash.h|g' libgrive/src/protocol/Json.cc
      
if [ "${CARCH}" = 'i686' ]; then
   sed -i '251s|m_last_sync.Sec() ) )|(boost::uint64_t)m_last_sync.Sec() ) )|g' libgrive/src/drive/State.cc
   sed -i '252s|m_last_sync.NanoSec() ) )|(boost::uint64_t)m_last_sync.NanoSec() ) )|g' libgrive/src/drive/State.cc
   sed -i '256s|m_cstamp) |(boost::uint64_t)m_cstamp) |g' libgrive/src/drive/State.cc
fi 

rm -rf build
  mkdir build
  cd build
  cmake .. -DCMAKE_BUILD_TYPE=Debug \
    -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_EXE_LINKER_FLAGS=-ljson-c