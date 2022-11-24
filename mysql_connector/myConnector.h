#pragma once
#include "pch.h"
#include "values.hpp"
extern "C"
{
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <mysql.h>

}

#include <vector>
#include <map>

extern "C" _declspec(dllexport) int setMyHandle(MYSQL * mysqlHandle, sqlValues valueSql);
extern "C" _declspec(dllexport) int QuerySql(MYSQL* mysqlHandle, const char* tableNmae, std::vector<std::string> column, const char* filter, std::map<std::string, std::vector<std::string>>& result);
extern "C" _declspec(dllexport) int InsertSql(MYSQL* mysqlHandle, const char* tableNmae, std::vector<std::string> column, std::vector<std::string> value);
extern "C" _declspec(dllexport) int InsertSqls(MYSQL* mysqlHandle, const char* tableName, std::vector<std::string> column, std::vector<std::vector<std::string>> values);
extern "C" _declspec(dllexport) int QueryDatabase(MYSQL* mysqlHandle, std::vector<std::string>& dataBases);
extern "C" _declspec(dllexport) int QueryTables(MYSQL* mysqlHandle, std::vector<std::string>& tables);
extern "C" _declspec(dllexport) int useDatabase(MYSQL* mysqlHandle, std::string dataBase);