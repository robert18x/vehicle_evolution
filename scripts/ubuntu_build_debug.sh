NCORES=`grep -c ^processor /proc/cpuinfo`
BUILD_THREADS=$(($NCORES + 2))

export CC=/usr/bin/gcc-10
export CXX=/usr/bin/g++-10

mkdir -p build && cd build
cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug ..
cmake --build . --config Debug --target all -- -j $BUILD_THREADS
