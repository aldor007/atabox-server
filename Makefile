COMP = g++
COMPFLAGS = -std=c++11
EXTERNAL = external
COMPINCLUDE = $(EXTERNAL)
COMPINCLUDE += -I $(EXTERNAL)/rocksdb_source/include
COMPLIBSDIR = libs
COMPLIBS = -lpthread -lmemenv   -lssl -lcrypto -lsnappy -lbz2  -lrt -lrocksdb -lz
all:
# g++ -std=c++11 main.cpp -L. -lrocksdb -I. -lpthread -lmemenv   -lssl -lcrypto -lsnappy -lbz2  -lrt
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
	cp $(EXTERNAL)/rocksdb_source/libmemenv.a libs/

rocksdb_lib:
	mkdir -p libs
	cd $(EXTERNAL)/rocksdb_source && make shared_lib
	cp $(EXTERNAL)/rocksdb_source/librocksdb.* libs/
	sudo cp libs/librocksdb.so /usr/lib/librocksdb.so
	cp $(EXTERNAL)/rocksdb_source/libmemenv.a libs/

clean:
	cd $(EXTERNAL)/rocksdb_source && make clean
	# rm *.o
	rm $(COMPLIBSDIR)/*


