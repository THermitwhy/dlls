#pragma once
#include <iostream>

struct sqlValues {
	const  char* host = "localhost";
	int port = 0;
	const  char* user = "root";
	const  char* passwd = "123456";
	const  char* database = "mysql";
	bool host_seted = false;
	bool port_seted = false;
	bool user_seted = false;
	bool passwd_seted = false;
	bool database_seted = false;
	void verify() {
		if (!host_seted) { std::cout << "host is deafault!"; }
		if (!port_seted) { std::cout << "port is deafault!"; }
		if (!user_seted) { std::cout << "user is deafault!"; }
		if (!passwd_seted) { std::cout << "passwd is deafault!"; }
		if (!database_seted) { std::cout << "database is deafault!"; };
	}
};
