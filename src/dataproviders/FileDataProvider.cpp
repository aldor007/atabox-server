#include <iostream>
#include <string>
#include "FileDataProvider.h"


FileDataProvider:: FileDataProvider(String filename):BaseDataProvider {
    this->filename = filename;
    this->connecionStatus = DBStatus::Open;

}


