COMP = g++
COMPFLAGS = -std=c++11
COMPINCLUDE = external
COMPINCLUDE += -I external/rocksdb_source/include
COMPLIBSDIR = libs
COMPLIBS = -lpthread -lmemenv   -lssl -lcrypto -lsnappy -lbz2  -lrt -lrocksdb -lz
all:
# g++ -std=c++11 main.cpp -L. -lrocksdb -I. -lpthread -lmemenv   -lssl -lcrypto -lsnappy -lbz2  -lrt
tests:
	$(COMP) $(COMPFLAGS)  -I $(COMPINCLUDE) -c $(COMPINCLUDE)/gmock-gtest-all.cc -o $(COMPINCLUDE)/gmock-gtest-all.o
	ar -rv $(COMPLIBSDIR)/libgmock.a $(COMPINCLUDE)/gmock-gtest-all.o
	$(COMP) $(COMPFLAGS)  test/RunAllTests.cpp -I $(COMPINCLUDE)/ -L $(COMPLIBSDIR)/ $(COMPLIBS) -lgtest -lgmock  -o run_tests
dataprovider:
	$(COMP) $(COMPFLAGS)  main.cpp -L $(COMPLIBSDIR)  -I $(COMPINCLUDE)  
rocksdb:
	cd external/rocksdb_source && make 
	cp external/rocksdb_source/librocksdb.* libs/
	cp external/rocksdb_source/libmemenv.a libs/

rocksdb_lib:
	cd external/rocksdb_source && make shared_lib
	cp external/rocksdb_source/librocksdb.* libs/
	cp external/rocksdb_source/libmemenv.a libs/

clean:
	cd external/rocksdb_source && make clean
	# rm *.o
	rm $(COMPLIBSDIR)/*


