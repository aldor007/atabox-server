

#ifndef EXECPOL_H_
#define EXECPOL_H_
#include <map>
#include <string>

#include "cpprest/json.h"
#include "utils/jsonextend.h"

namespace webjson = web::json;

#include <utils/atabox_log.h>
#include <recognition/PropertiesComparator.h>


typedef std::map<jsonextend, std::string>::iterator map_it;

std::string execution_policy_strict(std::map<jsonextend, std::string> &list, jsonextend &waveProperties) {
	PropertiesComparator comparator;
	for (map_it iterator = list.begin(); iterator != list.end(); iterator++) {
		double distance =  comparator.getDistance(iterator->first, waveProperties);
		LOG(debug)<<" Distance "<<distance;
		if (fabs(distance - 0) < 0.000001) { //FIXME: get compersion precision from config file
			return iterator->second;
		}
	}
	return "";
}
std::string execution_policy_nonstrict(std::map<jsonextend, std::string> &list, jsonextend &waveProperties) {
	PropertiesComparator comparator;
	double minDistance = 10000;
	std::string currentCommand;
	for (map_it iterator = list.begin(); iterator != list.end(); iterator++) {
		double distance =  comparator.getDistance(iterator->first, waveProperties);
		LOG(debug)<<"Distance "<<distance;
		if (minDistance > distance) {
			currentCommand = iterator->second;
			minDistance = distance;
		}
	}
	return  currentCommand;
}
#endif
