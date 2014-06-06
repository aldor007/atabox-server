

#include <map>
#include <string>

#include <utils/atabox_log.h>
#include <recognition/PropertiesComparator.h>
#include <wave/analysis/WaveProperties.h>


typedef std::map<WaveProperties, std::string>::iterator map_it;

std::string execution_policy_strict(std::map<WaveProperties, std::string> &list, WaveProperties &waveProperties) {
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
std::string execution_policy_nonstrict(std::map<WaveProperties, std::string> &list, WaveProperties &waveProperties) {
	PropertiesComparator comparator;
	double minDistance = 10000;
	std::string currentCommand;
	for (map_it iterator = list.begin(); iterator != list.end(); iterator++) {
		double distance =  comparator.getDistance(iterator->first, waveProperties);
		LOG(debug)<<" Distance "<<distance;
		if (minDistance > distance) {
			currentCommand = iterator->second;
			minDistance = distance;
		}
	}
	return currentCommand;
}
