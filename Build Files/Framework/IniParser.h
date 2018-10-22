#pragma once

#ifndef __INI_PARSER_H__
#define __INI_PARSER_H__

// Library includes:
#include <string>
#include <fstream>
#include <map>
#include <vector>

class IniParser
{
	// Member Methods:
public:
	bool LoadIniFile(const std::string& filename);
	std::string GetValueAsString(const std::string& iniSection, const std::string& key);
	int GetValueAsInt(const std::string& iniSection, const std::string& key);
	float GetValueAsFloat(const std::string& iniSection, const std::string& key);
	bool GetValueAsBoolean(const std::string& iniSection, const std::string& key);

protected:

private:	

	// Member Fields:
public:

protected:

private:
	std::map<std::string, std::string> maps;	
};

#endif // !__INI_PARSER_H__
