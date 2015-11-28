cd external
cmake CMakeLists.txt -DENABLE_OPENMP=OFF -DBUILD_EXAMPLES=OFF
cp aquila/libAquila.so ../libs/
cp aquila/lib/* ../libs/

cp casablanca/Release/Binaries/* ../libs

cp shark/lib/* ../libs
