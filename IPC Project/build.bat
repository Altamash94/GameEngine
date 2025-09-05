clear
#rm -r ./build

cmake -B build -G "Ninja" -DCMAKE_INSTALL_PREFIX=build/install -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=Debug -DENABLE_LOGGING=ON
ninja -C build install
build/install/bin/GameEngine
#gdb build/install/bin/GameEngine