#ifndef FILE_DATA_PROVIDER
#define FILE_DATA_PROVIDER
#include <iostream>
#include <string>
#include "BaseDataProvider.h"

template <typename KeyClass, typename ValueClass>
class FileDataProvider: public BaseDataProvider< KeyClass, ValueClass> {
        protected:
            String filename;
        public:
            FileDataProvider(String filename);
            ValueClass get(Keyclass key);
            bool set(Keyclass key, Valueclass value);
            std::vector<valueclass> getrangevalue(Keyclass startkey, Keyclass endkey);
}
#endif
