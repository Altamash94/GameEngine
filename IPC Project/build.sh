clear
rm -r ./build

cmake -G Ninja -B build -DCMAKE_INSTALL_PREFIX=build/install \
-DBUILD_SHARED_LIBS=ON \
-DCMAKE_BUILD_TYPE=Debug \
-DENABLE_LOGGING=ON
cmake --build build --target install

ninja -C build install