#include "SQLManager.h"
#include "Version.h"
#include <cstdio>
#include <filesystem>
using namespace std;

namespace {
	SQLManager* instance = nullptr;
}

bool SQLManager::setDatabasePath(const wstring& path)
{
	if (::instance == nullptr) {
		if (filesystem::exists(filesystem::path(path))) {
			FILE* file = nullptr;
			_wfopen_s(&file, path.c_str(), L"rb");
			if (file == nullptr) {
				return false;
			}
			else {
				fclose(file);
				::instance = new SQLManager(path);
				return true;
			}
		}
		else {
			FILE* file = nullptr;
			_wfopen_s(&file, path.c_str(), L"wb");
			if (file == nullptr) {
				return false;
			}
			else {
				fclose(file);
				::instance = new SQLManager(path);
				return true;
			}
		}
		::instance = new SQLManager(path);
		return true;
	}
	else {
		::instance->close();
		delete ::instance;
		::instance = nullptr;
		return setDatabasePath(path);
	}
}

SQLManager* SQLManager::getInstance()
{
	return ::instance;
}

bool SQLManager::isConnected() const
{
	return instance == nullptr;
}

int SQLManager::connect()
{
	if (instance == nullptr) {
		int res = sqlite3_open16(path.c_str(), &instance);
		return res;
	}
	else {
		return SQLITE_OK;
	}
}

int SQLManager::close()
{
	int res = sqlite3_close(instance);
	if (res == SQLITE_OK) {
		instance = nullptr;
	}
	return res;
}

const wchar_t* SQLManager::getErrorMessage()
{
	return static_cast<const wchar_t*>(sqlite3_errmsg16(instance));
}

int SQLManager::buildDatabase()
{
	if (!isConnected()) {
		return -1;
	}
	int res = 0;
	wstring sql;

	sql = L"CREATE TABLE IFM_VERSION(ID INTEGER PRIMARY KEY AUTOINCREMENT, "
		"Major INT NOT NULL, Minor INT NOT NULL, Fix INT NOT NULL, Build INT NOT NULL, "
		"UpdateTime CHAR(22) NOT NULL);";
	sqlite3_stmt* stmt;

	res = sqlite3_prepare16_v2(instance, sql.c_str(), static_cast<int>(wcslen(sql.c_str()) * 2), &stmt, nullptr);
	if (res != SQLITE_OK) {
		return res;
	}
	res = sqlite3_step(stmt);
	sqlite3_finalize(stmt);

	sql = L"INSERT INTO IFM_VERSION(Major, Minor, Fix, Build, UpdateTime) VALUES(" + to_wstring(IFM_VERSION_MAJOR)
		+ L", " + to_wstring(IFM_VERSION_MINOR) + L", " + to_wstring(IFM_VERSION_FIX) + L", " + to_wstring(IFM_VERSION_FIX)
		+ L", " + to_wstring(IFM_BUILD) + L", " + L"";
	return res;
}

SQLManager::SQLManager(const wstring& path)
{
	this->instance = nullptr;
	this->path = path;
}