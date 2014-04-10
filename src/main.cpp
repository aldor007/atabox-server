/*
 * main.cpp
 *
 *  Created on: 2 kwi 2014
 *      Author: mj
 */
#include <string>
#include "dataproviders/RocksdbProvider.h"
#include <map>
#include <iostream>
#include <random>

int main (int argc, char** argv){

	RocksdbProvider<std::string, std::string> db("test.db");
	std::string tmp = db.get("test");
	auto mapa = db.getAllKV();
	for(std::map<std::string, std::string>::iterator it = mapa.begin(); it != mapa.end(); it++)
		std::cout<<"key "<<it->first<< " value "<<mapa[it->first]<<'\n';
	std::cout<<tmp<<std::endl;
	return 0;
}



