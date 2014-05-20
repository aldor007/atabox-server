
#Rockdb
sudo apt-get install zlib1g-dev -y
sudo apt-get install zlib -y
sudo apt-get install libbzip2-dev -y
sudo apt-get install libsnappy-dev -y
sudo apt-get install libgflags2 -y
sudo apt-get install libgflags2-dev -y
sudo apt-get install libgflags-dev -y 
sudo apt-get install libbz2-dev -y
#test
# sudo apt-get install libgtest-dev -y
# sudo apt-get install google-mock -y 
#coverage
sudo apt-get install python-dev python-pip -y
sudo apt-get install lcov -y
sudo pip install gcovr
#boost
sudo apt-get install libboost1.54-all-dev libssl-dev cmake -y
sudo apt-get install libboost-atomic1.54.0 -y
sudo apt-get install libboost-filesystem1.54.0 -y
sudo apt-get install libboost-log-dev -y
sudo apt-get install libboost-log1.54.0 -y 
sudo apt-get install libboost-thread1.54.0 -y 
sudo apt-get install libboost1.54-dev -y 
#test
cd /tmp
 wget http://googletest.googlecode.com/files/gtest-1.7.0.zip
unzip gtest-1.7.0.zip
cd gtest-1.7.0
./configure
make
sudo cp -a include/gtest /usr/include
sudo cp -a lib/.libs/* /usr/lib/
cd /tmp
wget https://googlemock.googlecode.com/files/gmock-1.7.0.zip
unzip gmock-1.7.0
cd gmock-1.7.0
./configure
make
sudo cp -a include/gmock /usr/include
sudo cp -a lib/.libs/* /usr/lib/
sudo ldconfig -v | grep gtest
sudo ldconfig -v | grep gmock
