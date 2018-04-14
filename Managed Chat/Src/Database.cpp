#include "Database.h"
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>


Database::Database()
{
}


Database::~Database()
{
}


StorageProgramSource Database::ParseStorage(const std::string & filepath)
{
	std::ifstream stream(filepath);

	enum class StringType
	{
		NONE = -1, INDEX = 0, SOCKET = 1, TIME = 2, NAME = 3, MSG = 4
	};

	std::string line;
	std::stringstream ss[5];
	StringType type = StringType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#INDEX") != std::string::npos)
			type = StringType::INDEX;
		else if (line.find("#SOCKET") != std::string::npos)
			type = StringType::SOCKET;
		else if (line.find("#TIME") != std::string::npos)
			type = StringType::TIME;
		else if (line.find("#NAME") != std::string::npos)
			type = StringType::NAME;
		else if (line.find("#MSG") != std::string::npos)
			type = StringType::MSG;
		else
			ss[(int)type] << line << '\n';
	}
	return { ss[0].str(),ss[1].str(),ss[2].str(),ss[3].str(),ss[4].str() };
}
