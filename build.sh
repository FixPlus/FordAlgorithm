mkdir -p build
cmake CMakeLists.txt -B./build -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=./install -G "CodeBlocks - MinGW Makefiles"
mkdir -p install
cmake --build ./build --target install -- -j12
mkdir tests
