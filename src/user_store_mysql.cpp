#include <iostream>  

#include "user_store_mysql.h"

using namespace std;

extern "C" {
	#include "mysql.h"
}

UserStore::UserStore(char *host, char *database, char *username, char *password) {
	_host = host; 
	_database = database; 
	_username = username; 
	_password = password; 

	mysql_library_init(0, NULL, NULL);

	_mysqlHandler = mysql_init(NULL);
}

uint UserStore::init() {
	mysql_real_connect(
		_mysqlHandler,
		_host,
		_username,
		_password,
		_database,
		3306,
		nullptr, 
		0
	);

	return mysql_errno(_mysqlHandler);
}

uint UserStore::close() {
	mysql_close(_mysqlHandler);
	return mysql_errno(_mysqlHandler);
}

void UserStore::printErr(uint err) {
	cout << mysql_error(_mysqlHandler) << endl;
}

UserStore::~UserStore() {
	mysql_library_end();
}
