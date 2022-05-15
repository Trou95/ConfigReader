#include "ConfigReader.h"

ConfigReader::ConfigReader(){
	_file.exceptions(std::ios::badbit | std::ios::failbit);
}

ConfigReader::ConfigReader(const char* filepath) : ConfigReader() {
	_filepath = filepath;
}

long long ConfigReader::getFileLen()
{
	std::ifstream in(_filepath, std::ifstream::ate | std::ifstream::binary);
	auto result = in.tellg();
	in.close();
	return result;
}

eReadState ConfigReader::ReadConfig()
{
	if (!_filepath.c_str())
		return eReadState::READSTATE_FAIL;
	
	int len = getFileLen();
	if (len > -1)
	{
		_file.open(_filepath.c_str(), std::ios::in | std::ios::binary);
		if (_file.is_open())
		{
			size_t index = 0;
			char* tmp = nullptr;
			long long len = getFileLen() + 1;
			tmp = new char[len];
			assert(tmp && "Allocation Fail");
			memset(tmp, 0, len);
			_file.read(&tmp[0], len - 1);
			_filetext.clear();
			_filetext.append(tmp);
			auto str = getLine(index);
			while (str != nullptr)
			{
				addValue(*str);
				delete str;
				str = getLine(index);
			}
			_file.close();
			delete[] tmp;
			return eReadState::READSTATE_SUCCESS;
		}
	}
	return eReadState::READSTATE_FAIL;
}

bool ConfigReader::SaveFile()
{
	if (!_filepath.c_str())
		return false;
	try
	{
		_file.open(_filepath, std::ios::out | std::ios::binary | std::ios::trunc);
		if (_file.is_open())
		{
			_file.clear();
			for (auto p : _configs)
			{
				std::string tmp;
				tmp.append(p->name + "=" + p->value + "\n");
				_file.write(tmp.c_str(), tmp.length());
			
			}
		}
		_file.close();
	}
	catch(std::ios_base::failure& e)
	{
		
	}
	return true;
}


bool ConfigReader::IsValidValue(const std::string& str) const
{
	return str.find('=') < str.length();
}

bool ConfigReader::IsFound(const std::string& str) const
{
	for (auto p : _configs)
		if (p->name == str)
			return true;
	return false;
}

const std::string* ConfigReader::getLine(size_t& index) const
{
	size_t len = _filetext.length();
	#if COMMENT_CHR
	if (index < len && _filetext[index] == COMMENT_CHR)
	{
		index = findNextLine(index);
		return nullptr;
	}
	#endif
	for (size_t i = index; i <= len; i++)
	{
		if (i == len || _filetext[i] == '\n')
		{
			auto result = new std::string(_filetext.substr(index, i - index));
			index = i + 1;
			return result;
		}
	}
	index = len;
	return nullptr;
}

const size_t ConfigReader::findNextLine(size_t& index) const
{
	for (; _filetext[index]; index++)
	{
		if (_filetext[index] == '\n')
			return index;
	}
	return index;
}

const std::vector<stConfig*>& ConfigReader::getConfig() const
{
	return this->_configs;
}

void ConfigReader::addValue(const std::string& str) const
{
	size_t index = str.find('=');
	if (index && index < str.length())
	{
		std::string tmp = str.substr(0, index);
		if (!IsFound(tmp))
			_configs.push_back(new stConfig({ tmp,str.substr(index + 1) }));
	}
		
}

const char* ConfigReader::getValue(const char* str) const
{
	for (auto p : _configs)
	{
		if (p->name == str)
			return p->value.c_str();
	}
	return nullptr;
}

int ConfigReader::getValueInt(const char* str) const
{
	return std::stoi(getValue(str));
}

float ConfigReader::getValueFloat(const char* str) const
{
	return std::stof(getValue(str));
}

bool ConfigReader::setValue(const char* str,const char* value) const
{
	for (auto p : _configs)
	{
		if (p->name == str)
		{
			p->value = value;
			return true;
		}
	}
	return false;
}




