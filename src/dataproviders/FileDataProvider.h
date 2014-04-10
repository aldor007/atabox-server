/*
#ifndef FILE_DATA_PROVIDER
#define FILE_DATA_PROVIDER
#include <iostream>
#include <string>
#include "BaseDataProvider.h"

template <class KeyClass, class ValueClass>
class FileDataProvider: public BaseDataProvider<KeyClass, ValueClass> {
        protected:
            std::string filename;
        public:
            FileDataProvider (std::string filename);
            ValueClass get(KeyClass key) {}
            bool set(KeyClass key, ValueClass value) {}
            std::vector<ValueClass> getrangevalue(KeyClass startkey, KeyClass endkey) {}
};
#endif
*/
