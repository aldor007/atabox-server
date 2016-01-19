/*
 * RocksdbProvider.h
 *
 *  Created on: 10 kwi 2014
 *      Author: aldor
 */

#ifndef ROCKSDBPROVIDER_H_
#define ROCKSDBPROVIDER_H_
#include <string>
#include <map>
#include <iostream>
#include <utils/ataboxexception.h>

#include "BaseDataProvider.h"
#include "rocksdb/db.h"


template <class KeyClass, class ValueClass>
class RocksdbProvider: public BaseDataProvider<KeyClass, ValueClass> {

    public:
        RocksdbProvider(std::string databasename);
        virtual ValueClass get(KeyClass key);
        virtual std::map<KeyClass, ValueClass> getAllKV();
        virtual bool put(KeyClass key, ValueClass value);
        virtual ~RocksdbProvider();

    protected:
        std::string databasename;
        rocksdb::DB* db = nullptr;
        rocksdb::Options options;
};
#endif /* ROCKSDBPROVIDER_H_ */
//TODO: http://stackoverflow.com/a/8752879
template<class Key, class Value>
RocksdbProvider<Key, Value>::~RocksdbProvider() {
    if (db != nullptr)
         delete db;
}

template <class Key, class Value>
RocksdbProvider<Key, Value>::RocksdbProvider(std::string filename): databasename(filename) {

    this->options.create_if_missing = true;
    rocksdb::Status status =  rocksdb::DB::Open(this->options, this->databasename.c_str(), &db);
    if(status.ok()) {
        this->connecionStatus = DBStatus::Open;
    }
    else {
        this->connecionStatus = DBStatus::Error;
        throw new ataboxException("Error openning conncetion to db");
    }

}

template <>
bool RocksdbProvider<std::string, std::string>::put(std::string key, std::string value) {
    rocksdb::Status status;
    status = this->db->Put(rocksdb::WriteOptions(), key, value);
    return status.ok();
}
template <class Key, class Value>
bool RocksdbProvider<Key, Value>::put(Key key, Value value) {
    rocksdb::Status status;
    status = this->db->Put(rocksdb::WriteOptions(), static_cast<std::string>(key), static_cast<std::string>(value));
    return status.ok();
}

template <class Key, class Value>
Value RocksdbProvider<Key, Value>::get(Key key) {
    rocksdb::Status status;
    std::string tmpValue;
    status = this->db->Get(rocksdb::ReadOptions(), static_cast<std::string>(key), &tmpValue);
    if (status.ok()) {
        Value value(tmpValue);
        return value;
    }
    else {
        return nullptr;
    }

}

template <>
std::string RocksdbProvider<std::string, std::string>::get(std::string key) {
    rocksdb::Status status;
    std::string value;
    status = this->db->Get(rocksdb::ReadOptions(), key, &value);
    if (status.ok()) {
        return value;
    }
    else {
        return nullptr;
    }

}
template <>
std::map<std::string, std::string>  RocksdbProvider<std::string, std::string>::getAllKV() {
    std::map<std::string, std::string> dbmap;
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
      for (it->SeekToFirst(); it->Valid(); it->Next()) {
         dbmap[it->key().ToString()] = it->value().ToString();
      }
      assert(it->status().ok());  // Check for any errors found during the scan
      delete it;
      return dbmap;
}

template <class Key, class Value>
std::map<Key, Value>  RocksdbProvider<Key, Value>::getAllKV() {
    std::map<Key, Value> dbmap;
    rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
      for (it->SeekToFirst(); it->Valid(); it->Next()) {
    try {
         dbmap[Key(it->key().ToString())] = Value(it->value().ToString());
    } catch(std::exception &e) {

    }
      }
      assert(it->status().ok());  // Check for any errors found during the scan
      delete it;
      return dbmap;
}


