/*
 * WaveProperties.cpp
 *
 *  Created on: 9 kwi 2014
 *      Author: mj
 */

#include "WaveProperties.h"
#include <cpprest/json.h>
#include <sstream>

WaveProperties::WaveProperties() {
	// TODO Auto-generated constructor stub

}

WaveProperties::WaveProperties(std::string data) {
	// TODO Auto-generated constructor stub

}

WaveProperties::~WaveProperties() {
	// TODO Auto-generated destructor stub
}


std::string WaveProperties::toString() {

	json::value result = this->toJSON();
	return result.to_string();
}

json::value WaveProperties::toJSON() {

	json::value result;
	result["amplitude"] = json::value::number(amplitude);
	result["zeroCrossings"] = json::value::number(zeroCrossings);
	result["percentageAbove90percentage"] = json::value::number(percentageAbove90percentage);
	result["percentageAbove90percentage"] = json::value::number(percentageAbove80percentage);
	result["percentageAbove70percentage"] = json::value::number(percentageAbove70percentage);
	result["percentageAbove60percentage"] = json::value::number(percentageAbove60percentage);
	result["percentageAbove50percentage"] = json::value::number(percentageAbove50percentage);
	result["percentageAbove40percentage"] = json::value::number(percentageAbove40percentage);
	result["percentageAbove30percentage"] = json::value::number(percentageAbove30percentage);
	result["percentageAbove20percentage"] = json::value::number(percentageAbove20percentage);
	result["percentageAbove10percentage"] = json::value::number(percentageAbove10percentage);
	return result;
}

/*
 * #include <cpprest/json.h>
#include <sstream>

using namespace std;
typedef web::json::value JsonValue;
typedef web::json::value::value_type JsonValueType;
typedef std::wstring String;
typedef std::wstringstream StringStream;

String JsonValueTypeToString(const JsonValueType& type)
{
  switch (type)
	{
		case JsonValueType::Array: return L"Array";
		case JsonValueType::Boolean: return L"Boolean";
		case JsonValueType::Null: return L"Null";
		case JsonValueType::Number: return L"Number";
		case JsonValueType::Object: return L"Object";
		case JsonValueType::String: return L"String";
	}
}

void Externalize(const JsonValue& json)
{
	for (auto iter = json.cbegin(); iter != json.cend(); ++iter)
	{
		auto k = iter->first;
		auto v = iter->second;

		auto key = k.as_string();
		auto value = v.to_string();

		wcout << key << L" : " << value << " (" << JsonValueTypeToString(v.type()) << ")" << endl;
	}
}

void Test1_json_serialize()
{
	JsonValue json;

	json[L"key1"] = JsonValue::boolean(false);
	json[L"key2"] = JsonValue::number(44);
	json[L"key3"] = JsonValue::number(43.6);
	json[L"key4"] = JsonValue::string(U("str"));

	Externalize(json);

	json.serialize(wcout);
}

void Test2_json_deserialize()
{
	StringStream ss;

	ss << U("{\"key1\":false,\"key2\":44,\"key3\":43.6,\"key4\":\"str\"}");

	JsonValue json = JsonValue::parse(ss);

	Externalize(json);

	json.serialize(wcout);
}

int main()
{
	wcout << "Running test 1" << endl;
	Test1_json_serialize();

	wcout << endl << "Running test 2" << endl;
	Test2_json_deserialize();
	return 0;
}
 */
