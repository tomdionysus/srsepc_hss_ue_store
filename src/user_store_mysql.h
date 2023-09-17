#ifndef SRSRAN_HSS_USERSTORE
#define SRSRAN_HSS_USERSTORE 1

extern "C" {
	#include "mysql.h"
	#include <netinet/in.h>
	#include <arpa/inet.h>
}

enum auth_type { auth_type_unknown, auth_type_xor, auth_type_mil };
enum op_type { op_type_unknown, op_type_op, op_type_opc };

typedef struct user_context {
	uint64_t imsi;
	char name[256];
	auth_type auth;
	char key_identifier[16];
	op_type op;
	char op_opc[16];
	char amf[2];
	uint64_t sqn;
	uint8_t qci;
	bool dynamic_ip;
	in_addr ip_alloc;
} user_context_t;

#define SRSRAN_HSS_USERSTORE_MIN_OF(a,b) (a < b ? a : b)

class UserStore {  
	public:
		UserStore(char *host, char *database, char *username, char *password);
		~UserStore();

		uint init();
		uint close();

		bool getUser(uint64_t ssid, user_context_t *ctx);

		void printErr(uint err);

	private:

		char *_host;
		char *_database;
		char *_username;
		char *_password;

		MYSQL *_mysqlHandler;
};  

#endif