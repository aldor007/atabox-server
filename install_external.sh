cd external
cmake CMakeLists.txt -DENABLE_OPENMP=OFF -DBUILD_EXAMPLES=OFF
make -j 2

mkdir -p ../libs

cp aquila/libAquila.* ../libs/
cp aquila/lib/* ../libs/

cp casablanca/Release/Binaries/* ../libs

cp shark/lib/* ../libs
