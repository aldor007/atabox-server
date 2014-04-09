#include "dataproviders/RocksdbProvider.h"
#include <map>

template<class Key, class Value>
RocksdbProvider<Key, Value>::~RocksdbProvider() {
	 delete db;
}
template <class Key, class Value>
RocksdbProvider<Key, Value>::RocksdbProvider(std::string filename) {
	this->databasename = filename;
	this->options.create_if_missing = true;
	rocksdb::Status status =  rocksdb::DB::Open(this->options, this->databasename.c_str(), &db);
	if(status.ok()) {
		this->connecionStatus = DBStatus::Open;
	}
	else {
		this->connecionStatus = DBStatus::Error;
	}
}

template <class Key, class Value>
bool RocksdbProvider<Key, Value>::set(Key key, Value value) {
	rocksdb::Status status;
	status = this->Put(rocksdb::WriteOptions(), key, value);
	return status.ok();
}

template <class Key, class Value>
Value RocksdbProvider<Key, Value>::get(Key key) {
	rocksdb::Status status;
	Value value;
	status = this->Put(rocksdb::WriteOptions(), key, &value);
	if (status.ok()) {
		return value;
	}
	else {
		return nullptr;
	}

}

template <class Key, class Value>
std::map<Key, Value>  RocksdbProvider<Key, Value>::getAllKV() {
	std::map<std::string, Value> dbmap;
	rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
	  for (it->SeekToFirst(); it->Valid(); it->Next()) {
		//cout << it->key().ToString() << ": "  << it->value().ToString() << endl;
		 dbmap[it->key().ToString()] = it->value().ToString();
	  }
	  assert(it->status().ok());  // Check for any errors found during the scan
	  delete it;
	  return dbmap;
}

