// This include:
#include "IniParser.h"

// Local includes:
#include "LogManager.h"

// Library includes:
#include <string>
#include <map>



std::string
IniParser::GetValueAsString(const std::string& iniSection, const std::string& key)
{
	std::string value = "";

	std::string myKey = iniSection + "|" + key;
	auto iter = maps.find(myKey);

	if (iter != maps.end())
	{
		value = iter->second;
	}
	else
	{
		LogManager::GetInstance().Log("Not found!");
	}

	return value;
}

bool
IniParser::GetValueAsBoolean(const std::string& iniSection, const std::string& key)
{
	bool result = false;

	std::string value = GetValueAsString(iniSection, key);
	
	if (value == "true")
	{
		result = true;
	}

	return result;
}

int
IniParser::GetValueAsInt(const std::string& iniSection, const std::string& key)
{
	int result;

	std::string value = GetValueAsString(iniSection, key);
	result = std::stoi(value);
	
	return result;
}

float
IniParser::GetValueAsFloat(const std::string& iniSection, const std::string& key)
{
	float result;

	std::string value = GetValueAsString(iniSection, key);
	result = std::stof(value);

	return result;
}