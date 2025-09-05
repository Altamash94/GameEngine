clear
#rm -r ./build

cmake -B build -DCMAKE_INSTALL_PREFIX=build/install \
-DBUILD_SHARED_LIBS=ON \
-DCMAKE_BUILD_TYPE=Debug \
-DENABLE_LOGGING=ON
cmake --build build --target install

make install

#build/install/bin/GameEngine
#gdb build/install/bin/GameEngine