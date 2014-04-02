#ifndef ROCKSDB__DATA_PROVIDER
#define ROCKSDB_DATA_PROVIDER

#include <iostream>
#include <string>
#include "BaseDataProvider.h"

template <typename KeyClass, typename ValueClass>
class RocksdbProvider: public BaseDataProvider< KeyClass, ValueClass> {
        protected:
            String databasename;
        public:
            FileDataProvider(String databasename);
            ValueClass get(Keyclass key);
            bool set(Keyclass key, Valueclass value);
            std::vector<Valueclass> getrangevalue(Keyclass startkey, Keyclass endkey);
}
#endif
