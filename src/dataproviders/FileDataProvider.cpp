#include <iostream>
#include <string>
#include "dataproviders/FileDataProvider.h"

template <class KeyClass, class ValueClass>
FileDataProvider<KeyClass, ValueClass>::FileDataProvider(std::string filename):
BaseDataProvider<KeyClass, ValueClass>() {
    this->filename = filename;
    this->connecionStatus = DBStatus::Open;

}



