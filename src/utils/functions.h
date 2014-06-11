/*
 * functions.h
 *
 *  Created on: 8 cze 2014
 *      Author: aldor
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <sys/stat.h>

#include "wave/analysis/Property.h"

#include "recognition/ProcessAndAnalyze.h"


/*PROPERTY*/
#include "wave/analysis/AmplitudeProperty.h"
#include "wave/analysis/LengthProperty.h"
#include "wave/analysis/ZeroCrossingsProperty.h"
#include "wave/analysis/PercentageAboveProperty.h"
#include "wave/analysis/WhereIsAmplitudeProperty.h"
#include "wave/analysis/AverageValueProperty.h"

#include "wave/analysis/SpectrumProperty.h"

/*FILTER*/

#include "wave/processing/preprocessing/SilenceCuttingFilter.h"
#include "wave/processing/preprocessing/NormalizingFilter.h"

#include "wave/processing/postprocessing/HannWindowFilter.h"
#include "wave/processing/postprocessing/FastFourierTransformFilter.h"

class Config {
private:
	static web::json::value m_config;
        typedef std::vector<std::pair<utility::string_t, web::json::value>> storage_type;
        typedef storage_type::iterator iterator;
        typedef storage_type::const_iterator const_iterator;
	std::string get_file_contents(std::string filename)
	{
	  std::ifstream in(filename.c_str(), std::ios::in | std::ios::binary);
	  if (in)
	  {
	    std::string contents;
	    in.seekg(0, std::ios::end);
	    contents.resize(in.tellg());
	    in.seekg(0, std::ios::beg);
	    in.read(&contents[0], contents.size());
	    in.close();
	    return(contents);
	  }
	  throw(errno);
	}
public:
	Config() {
	}
	void loadFromFile(std::string filename) {

	    struct stat buffer;

	    if (stat (filename.c_str(), &buffer) != 0) {
	    	LOG(error)<<"Config file not found! " <<filename;
	    	setDefaultValues();
	    	return;
	    }
	    	LOG(debug)<<"Confi2g";
		std::string instring = get_file_contents(filename);

		m_config = web::json::value::parse(instring.c_str());
		LOG(debug)<<"Loaded config "<<m_config.to_string();


	}
	web::json::value operator[](std::string key) const {
		return m_config[key];
	}
	const_iterator cbegin() {
		return m_config.as_object().cbegin();
	}
	const_iterator cend() {
		return m_config.as_object().cend();
	}
	web::json::value get(std::string key, web::json::value def) {
		if (m_config[key].is_null())
			return def;
		return m_config[key];
	}
	void setDefaultValues() {
        jsonextend tmpobject;
        /*
        tmpobject["weight"] = web::json::value::number(1.0);
        tmpobject["additional"] = web::json::value
		m_config["NormalizingFilter"] = web::json::value*/
	}
};
web::json::value Config::m_config = web::json::value::parse("{}");



extern Config g_config;

void init_ProcessAndAnalize(ProcessAndAnalyze &monstru) {


	Processor * firstProcessor = new Processor();
	firstProcessor->addToFilterChain(new NormalizingFilter(1.0));
	firstProcessor->addToFilterChain(new SilenceCuttingFilter(0.2));
	SamplesAnalizator * firstAnalizator = new SamplesAnalizator();
	firstAnalizator->addProperty(new AmplitudeProperty(0, 100, 2.2));
	firstAnalizator->addProperty(new LengthProperty(1.7));
	firstAnalizator->addProperty(new ZeroCrossingsProperty(0, 100, 1.5));
	firstAnalizator->addProperty(new ZeroCrossingsProperty(50, 100, 0.5));
	firstAnalizator->addProperty(new PercentageAboveProperty(0.5, 3.0));
	firstAnalizator->addProperty(new WhereIsAmplitudeProperty(0.75));
	firstAnalizator->addProperty(new AverageValueProperty(0, 80, 0.2));

	monstru.add(std::make_pair(firstProcessor, firstAnalizator ));
	Processor * secondProssor = new Processor();
	secondProssor->addToFilterChain(new HannWindowFilter());
	secondProssor->addToFilterChain(new FastFourierTransformFilter());
	SamplesAnalizator * secondAnalizator = new SamplesAnalizator();
	secondAnalizator->addProperty(new SpectrumProperty(0.85));
	monstru.add(std::make_pair(secondProssor, secondAnalizator));



}
void init_ProcessAndAnalizeConfig(ProcessAndAnalyze &monstru) {

	uint16_t processors_ct = g_config.get("number_of_processors",
	                                       web::json::value::number(1)).as_integer();
    uint16_t analizators_ct = g_config.get("number_of_analizators",
	                                       web::json::value::number(2)).as_integer();


	Processor **processors = new Processor*[ processors_ct ];

	SamplesAnalizator ** analizators = new SamplesAnalizator*[analizators_ct];



	Processor * firstProcessor = new Processor();
		firstProcessor->addToFilterChain(new NormalizingFilter(1.0));
		firstProcessor->addToFilterChain(new SilenceCuttingFilter(0.2));
		SamplesAnalizator * firstAnalizator = new SamplesAnalizator();
		int step = 10;
		for (int i = 0; i < 100; i += step) {
			firstAnalizator->addProperty(new AmplitudeProperty(i, i + step));
			firstAnalizator->addProperty(new PercentageAboveProperty(0.01 * i));
			firstAnalizator->addProperty(new ZeroCrossingsProperty(i, i + step));
			firstAnalizator->addProperty(new AverageValueProperty(i, i + step));
		}
		firstAnalizator->addProperty(new LengthProperty());
		firstAnalizator->addProperty(new WhereIsAmplitudeProperty());

		monstru.add(std::make_pair(firstProcessor, firstAnalizator));


}
#endif /* FUNCTIONS_H_ */
