COMP = g++
COMPFLAGS = -std=c++11
COMPINCLUDE = external/
COMPLIBSDIR = libs/
COMPLIBS = -lrocksdb -lpthread -lssl -lcrypto -lsnappy -lbz2 -lrt
all:
# g++ -std=c++11 main.cpp -L. -lrocksdb -I. -lpthread -lmemenv   -lssl -lcrypto -lsnappy -lbz2  -lrt
tests:
	$(COMP) $(COMPFLAGS)  -I $(COMPINCLUDE) -c $(COMPINCLUDE)gmock-gtest-all.cc -o $(COMPINCLUDE)gmock-gtest-all.o
	ar -rv $(COMPLIBSDIR)libgmock.a $(COMPINCLUDE)gmock-gtest-all.o
	$(COMP) $(COMPFLAGS)  test/RunAllTests.cpp -I $(COMPINCLUDE) -L $(COMPLIBSDIR) $(COMPLIBS) -lgtest -lgmock  -o run_tests
dataprovider:
	$(COMP) $(COMPFLAGS)  main.cpp -I $(COMPINCLUDE) -L $(COMPLIBSDIR) $(COMPLIBS)
rocksdb:
	cd external/rocksdb_source && make 

rocksdb_lib:
	cd external/rocksdb_source && make shared_lib
	cp external/rocksdb_source/librocksdb.a libs/
	cp external/rocksdb_source/libmemeenv.a libs/

clean:
	cd external/rocksdb_source && make clean


