#include <iostream>
#include <string>
#include "BaseDataProvider.h"

template <typename KeyClass, typename ValueClass>
class FileDataProvider: BaseDataProvider< KeyClass, ValueClass> {
        protected:
            String filename;
        public:
            FileDataProvider(String filename);
            ValueClass get(keyclass key);
            bool set(keyclass key, valueclass value);
            std::vector<valueclass> getrangevalue(keyclass startkey, keyclass endkey);
}
