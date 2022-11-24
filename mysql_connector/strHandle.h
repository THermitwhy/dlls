#pragma once
#include "pch.h"
#include <iostream>
#include <vector>
int paramToSql(std::vector<std::string> param, std::string tableName, std::string filter, std::string& sql);
int paramToInsertSql(std::string tableName, std::vector<std::string> column, std::vector<std::string> value, std::string& sql);