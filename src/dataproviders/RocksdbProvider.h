#ifndef ROCKSDB__DATA_PROVIDER
#define ROCKSDB_DATA_PROVIDER

#include <iostream>
#include <string>
#include <map>
#include "dataproviders/BaseDataProvider.h"
#include "rocksdb/db.h"

template <class KeyClass,class ValueClass>
class RocksdbProvider: public BaseDataProvider<KeyClass, ValueClass> {
        protected:
            std::string databasename;
            rocksdb::DB* db;
            rocksdb::Options options;

        public:
            RocksdbProvider(std::string databasename);
            ValueClass get(KeyClass key);
            std::map<KeyClass, ValueClass> getAllKV();
            bool set(KeyClass key, ValueClass value);
            ~RocksdbProvider();
};
#endif
