[![Build Status](http://j.marcinkaciuba.pl/job/Atabox/badge/icon)](http://j.marcinkaciuba.pl/job/Atabox/)
# atabox-server #

Basic voice command(saved in database) executor.

### What is this repository for? ###

work in progress
### How do I get set up? ###


#### Summary of set up###
```bash
atabox_deps.sh
git submodule init
git submodule update
make casablanca
make rocksdb
```

####How to run tests####
```bash
cd DebugTest
make clean && make -j 4 all
cd ..
./DebugTest/atabox-server
```

### Contribution guidelines ###

* Writing tests
* Code review
* Other guidelines

### Who do I talk to? ###

* Repo owner or admin
* Other community or team contact
