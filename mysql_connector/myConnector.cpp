#include "pch.h"
#include "myConnector.h"
#include "strHandle.h"


int setMyHandle(MYSQL* mysqlHandle, sqlValues valueSql)
{
    valueSql.verify();
    mysql_init(mysqlHandle);
    if (mysql_real_connect(mysqlHandle, valueSql.host, valueSql.user, valueSql.passwd, valueSql.database, valueSql.port, NULL, 0)) {
        printf("successful! connect to mysql\n");
        return 1;
    }
    else {
        printf("error!\n");
        return 0;
    }

}

int QuerySql(MYSQL* mysqlHandle, const char* tableNmae, std::vector<std::string> column, const char* filter, std::map<std::string, std::vector<std::string>>& result)
{
    MYSQL_RES* result_ptr; /*指向查询结果的指针*/
    MYSQL_FIELD* field_ptr; /*字段结构指针*/
    MYSQL_ROW result_row;//按行存储结果
    int resultRows;
    std::vector<std::string> columns;
    std::string sql;
    if (paramToSql(column, tableNmae, filter, sql)) { return 1; }
    if (mysql_query(mysqlHandle, sql.c_str())) { return 2; };
    result_ptr = mysql_store_result(mysqlHandle);
    if (!result_ptr) { return 3; }
    resultRows = mysql_num_rows(result_ptr) + 1;
    for (int i = 0; field_ptr = mysql_fetch_field(result_ptr); i++) {
        columns.push_back(field_ptr->name);
    }
    std::vector<std::vector<std::string>> results;
    results.resize(columns.size());
    for (int i = 1; i < resultRows; i++)
    {
        result_row = mysql_fetch_row(result_ptr);

        for (int j = 0; j < columns.size(); j++) {
            //printf("%st", result_row[j]);
            results[j].push_back(result_row[j]);
        }

    }
    for (int i = 0; i < columns.size(); i++) {
        result.insert(std::pair<std::string, std::vector<std::string>>(columns[i], results[i]));
    }
    return 0;
}

int InsertSqls(MYSQL* mysqlHandle, const char* tableName, std::vector<std::string> column, std::vector<std::vector<std::string>> values)
{
    if ((!column.size() | !values.size()) | (column.size() != values[0].size())) { return 1; }
    for (auto field : values) {
        std::string sql;
        paramToInsertSql(tableName, column, field, sql);
        int res = mysql_query(mysqlHandle, sql.c_str());
        if (res) { return 1; };
    }
    return 0;
}

int QueryDatabase(MYSQL* mysqlHandle, std::vector<std::string>& dataBases)
{
    MYSQL_RES* result_ptr; /*指向查询结果的指针*/
    MYSQL_FIELD* field_ptr; /*字段结构指针*/
    MYSQL_ROW result_row;//按行存储结果
    int resultRows;
    if (mysql_query(mysqlHandle, "show Databases")) { return 1; };
    result_ptr = mysql_store_result(mysqlHandle);
    if (!result_ptr) { return 3; }
    resultRows = mysql_num_rows(result_ptr) + 1;
    for (int i = 1; i < resultRows; i++)
    {
        result_row = mysql_fetch_row(result_ptr);
        dataBases.push_back(result_row[0]);
    }

    return 0;
}

int QueryTables(MYSQL* mysqlHandle, std::vector<std::string>& tables)
{
    MYSQL_RES* result_ptr; /*指向查询结果的指针*/
    MYSQL_FIELD* field_ptr; /*字段结构指针*/
    MYSQL_ROW result_row;//按行存储结果
    int resultRows;
    if (mysql_query(mysqlHandle, "show Tables")) { return 1; };
    result_ptr = mysql_store_result(mysqlHandle);
    if (!result_ptr) { return 3; }
    resultRows = mysql_num_rows(result_ptr) + 1;
    for (int i = 1; i < resultRows; i++)
    {
        result_row = mysql_fetch_row(result_ptr);
        tables.push_back(result_row[0]);
    }

    return 0;
}

int useDatabase(MYSQL* mysqlHandle, std::string dataBase)
{
    std::string database = "use " + dataBase;
    mysql_query(mysqlHandle, database.c_str());
    return 0;
}

