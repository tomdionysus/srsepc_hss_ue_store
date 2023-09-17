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

bool UserStore::getUser(uint64_t ssid, user_context_t *ctx) {
	string query = "SELECT `imsi`, `name`, `auth`, `key_identifier`, `op_type`, `op_opc`, `amf`, `sqn`, `qci`, `ip_alloc` FROM `user` WHERE `imsi` = ";
	query += to_string(ssid);

	bool success = false;
	int err = mysql_query(_mysqlHandler, query.c_str());

	if(err) { return false; }

	MYSQL_RES * result = mysql_store_result(_mysqlHandler);

	if(result != nullptr) {
		if(mysql_num_rows(result)!=0) {
			MYSQL_ROW row = mysql_fetch_row(result);
			uint num_fields = mysql_num_fields(result);
			if(num_fields == 10) {
				// Get Lengths
				unsigned long *lengths = lengths = mysql_fetch_lengths(result);
				
				// Get IMSI
				ctx->imsi = std::stoull(row[0]);

				// Get Name
				memcpy(ctx->name, (const char*)row[1], SRSRAN_HSS_USERSTORE_MIN_OF(lengths[1], 255));
				ctx->name[lengths[1]] = 0;

				// Get Auth Type
				ctx->auth = auth_type_unknown;
				if(strcmp("xor",row[2]) == 0) { ctx->auth = auth_type_xor; }
				if(strcmp("mil",row[2]) == 0) { ctx->auth = auth_type_mil; }

				// Get KI
				memcpy(ctx->key_identifier, (const char*)row[3], SRSRAN_HSS_USERSTORE_MIN_OF(lengths[3], 16));

				// Get OP / OPC Type
				ctx->op = op_type_unknown;
				if(strcmp("op",row[4]) == 0) { ctx->op = op_type_op; }
				if(strcmp("opc",row[4]) == 0) { ctx->op = op_type_opc; }

				// Get OP/OPC
				memcpy(ctx->op_opc, (const char*)row[5], SRSRAN_HSS_USERSTORE_MIN_OF(lengths[5], 16));

				// Get AMF
				memcpy(ctx->amf, (const char*)row[6], SRSRAN_HSS_USERSTORE_MIN_OF(lengths[6], 2));

				// Get SQN
				ctx->sqn = std::stoull(row[7]);

				// Get QCI
				ctx->qci = atoi(row[8]);

				// Get IP or dynamic
				if(strcmp("dynamic",row[9]) == 0) {
					ctx->dynamic_ip = true;
					memset(&(ctx->ip_alloc), 0, 4);
				} else {
					ctx->dynamic_ip = false;
					inet_aton(row[9], &(ctx->ip_alloc));
				}
			}
		} 
		mysql_free_result(result);
	} 

	return success;
}

void UserStore::printErr(uint err) {
	cout << mysql_error(_mysqlHandler) << endl;
}

UserStore::~UserStore() {
	mysql_library_end();
}
