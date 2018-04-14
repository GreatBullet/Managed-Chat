#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
struct StorageProgramSource {
	std::string IndexSource;
	std::string SocketSource;
	std::string TimeSource;
	std::string NameSource;
	std::string MessageSource;

};
class Database
{
public:
	Database();
	~Database();
	StorageProgramSource ParseStorage(const std::string& filepath);

};

