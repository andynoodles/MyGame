#cmake --build build && cmake -B build
mkdir -p build 
cmake --build build &&  cmake -DCMAKE_BUILD_TYPE=Debug -B build && ./build/pacman
