#pragma once
#include "stdafx.h"
#include <string>
#include "sqlite3.h"
class SQLManager
{
public:
	static bool setDatabasePath(const std::wstring& path);
	static SQLManager* getInstance();
	bool isConnected() const;
	int connect();
	int close();
	const wchar_t* getErrorMessage();
	int buildDatabase();
	struct Version {
		int id;
		std::wstring time;
		uint major;
		uint minor;
		uint fix;
		uint build;
	};
private:
	SQLManager(const std::wstring& path);
	sqlite3* instance;
	std::wstring path;
};

