/*
 * RocksdbProvider.h
 *
 *  Created on: 10 kwi 2014
 *      Author: aldor
 */

#ifndef ROCKSDBPROVIDER_H_
#define ROCKSDBPROVIDER_H_
#include "BaseDataProvider.h"
#include "rocksdb/db.h"

template <class KeyClass,class ValueClass>
class RocksdbProvider: public BaseDataProvider<KeyClass, ValueClass> {
        protected:
            std::string databasename;
            rocksdb::DB* db;
            rocksdb::Options options;

        public:
            RocksdbProvider(std::string databasename);
            virtual ValueClass get(KeyClass key);
            virtual std::map<KeyClass, ValueClass> getAllKV();
            virtual bool set(KeyClass key, ValueClass value);
            virtual ~RocksdbProvider();
};
#endif /* ROCKSDBPROVIDER_H_ */
