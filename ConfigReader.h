
// ConfigReader 1.0
// Read/Write configs to file and use them whenever you want
// Its also supports comments (# Default) to leave comment above
// Author: Gorkem95

#ifndef CONFIGREADER_H_
#define CONFIGREADER_H_

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <type_traits>
#include <assert.h>



#define COMMENT_CHR 35



enum class eReadState
{
	READSTATE_SUCCESS,
	READSTATE_FAIL
};

struct stConfig
{
	std::string name;
	std::string value;
};


class ConfigReader
{
private:
	std::string _filepath;
	std::fstream _file;
	std::string _filetext;
	mutable std::vector<stConfig*> _configs;

	long long getFileLen();
	const std::string* getLine(size_t& index) const;
	const size_t findNextLine(size_t& index) const;
	bool IsValidValue(const std::string& str) const;
	bool IsFound(const std::string& str) const;

public:
	ConfigReader();
	ConfigReader(const char *filepath);
	eReadState ReadConfig();
	bool SaveFile();
	const std::vector<stConfig*>& getConfig() const;
	void addValue(const std::string& str) const;
	const char* getValue(const char* str) const;
	int getValueInt(const char* str) const;
	float getValueFloat(const char* str) const;
	bool setValue(const char* str, const char* value) const;
	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	bool setValue(const char* str, T value) const { return setValue(str, std::to_string(value).c_str()); };
};



#endif