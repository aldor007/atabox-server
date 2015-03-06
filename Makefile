COMP = g++
COMPFLAGS = -std=c++11
EXTERNAL = external
COMPINCLUDE = $(EXTERNAL)
COMPINCLUDE += -I $(EXTERNAL)/rocksdb_source/include
COMPLIBSDIR = libs
COMPLIBS = -lpthread -lmemenv   -lssl -lcrypto -lsnappy -lbz2  -lrt -lrocksdb -lz
all: rocksdb_lib casablanca aquila
tests:
	$(COMP) $(COMPFLAGS)  -I $(COMPINCLUDE) -c $(EXTERNAL)/gmock-gtest-all.cc -o $(EXTERNAL)/gmock-gtest-all.o
	ar -rv $(COMPLIBSDIR)/libgmock.a $(EXTERNAL)/gmock-gtest-all.o
	$(COMP) $(COMPFLAGS)  test/RunAllTests.cpp -I $(COMPINCLUDE) -L $(COMPLIBSDIR) $(COMPLIBS) -lgtest -lgmock  -o run_tests
dataprovider:
	$(COMP) $(COMPFLAGS)  main.cpp -L $(COMPLIBSDIR)  -I $(COMPINCLUDE)  
rocksdb:
	mkdir -p libs
	cd $(EXTERNAL)/rocksdb_source && make 

	cp $(EXTERNAL)/rocksdb_source/librocksdb.* libs/

rocksdb_lib:
	mkdir -p libs
	cd $(EXTERNAL)/rocksdb_source && make shared_lib
	cp $(EXTERNAL)/rocksdb_source/librocksdb.* libs/
	sudo cp libs/librocksdb.so /usr/lib/librocksdb.so
casablanca:
	mkdir -p libs
	mkdir -p $(EXTERNAL)/casablanca/Release/build.release
	cd $(EXTERNAL)/casablanca/Release/build.release &&	cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=OFF -DBUILD_SAMLPES=OFF && 	make && sudo make install
	cp $(EXTERNAL)/casablanca/Release/build.release/Binaries/libcpprest.so libs
	sudo cp $(EXTERNAL)/casablanca/Release/build.release/Binaries/libcpprest.so /usr/lib
aquila:
	cd ${EXTERNAL}/aquila/ && cmake CMakeLists.txt && make && sudo make install

	
clean:
	cd $(EXTERNAL)/rocksdb_source && make clean
	# rm *.o
	rm $(COMPLIBSDIR)/*


