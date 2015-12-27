#test
cd libs
 wget http://googletest.googlecode.com/files/gtest-1.7.0.zip
unzip gtest-1.7.0.zip
cd gtest-1.7.0
./configure CXX="g++ --std=c++11"
make
cp -a lib/.libs/* ../
cd ../../
cd libs
wget https://googlemock.googlecode.com/files/gmock-1.7.0.zip
unzip gmock-1.7.0
cd gmock-1.7.0
./configure CXX="g++ --std=c++11" --enable-static --disable-shared
make
cp -a lib/.libs/* ../
cd ..
