#include "pch.h"
#include "strHandle.h"

int paramToSql(std::vector<std::string> param, std::string tableName, std::string filter, std::string& sql)
{
	if ((param.size() <= 0) | (!sql.empty())) { return 1; }
	sql = "select ";
	int sizeparam = param.size();
	for (int i = 0; i < param.size() - 1; i++) {
		sql += param[i] + ",";
	}
	sql += param[param.size() - 1];
	sql += " from " + tableName + " where " + filter;
	return 0;

}

int paramToInsertSql(std::string tableName, std::vector<std::string> column, std::vector<std::string> value, std::string& sql)
{
	std::string columned;
	for (int i = 0; i < column.size() - 1; i++) {
		columned += column[i] + ",";
	}
	columned += column[column.size() - 1];
	std::string valued;
	for (int i = 0; i < value.size() - 1; i++) {
		valued += "\"" + value[i] + "\",";
	}
	valued += "\"" + value[value.size() - 1] + "\"";
	sql = "insert into " + tableName + " (" + columned + ")" + " values (" + valued + ")";
	return 0;
}
