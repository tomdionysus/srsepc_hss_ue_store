#ifndef SRSRAN_HSS_USERSTORE
#define SRSRAN_HSS_USERSTORE 1

extern "C" {
	#include "mysql.h"
}

class UserStore {  
	public:
		UserStore(char *host, char *database, char *username, char *password);
		~UserStore();

		uint init();
		uint close();

		void printErr(uint err);

	private:

		char *_host;
		char *_database;
		char *_username;
		char *_password;

		MYSQL *_mysqlHandler;
};  

#endif