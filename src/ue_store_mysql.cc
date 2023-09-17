/**
 * Copyright 2013-2023 Software Radio Systems Limited
 *
 * This file is part of srsRAN.
 *
 * srsRAN is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as
 * published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 *
 * srsRAN is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * A copy of the GNU Affero General Public License can be found in
 * the LICENSE file in the top-level directory of this distribution
 * and at http://www.gnu.org/licenses/.
 *
 */

#include "hdr/ue_store_mysql.h"

using namespace std;

namespace srsepc { 

ue_store_mysql::ue_store_mysql(std::string host, std::string database, std::string username, std::string password) {
	_host = host; 
	_database = database; 
	_username = username; 
	_password = password; 

	mysql_library_init(0, NULL, NULL);

	_mysql_handle = mysql_init(NULL);
}

ue_store_mysql::~ue_store_mysql() {
	mysql_library_end();
}

uint ue_store_mysql::init() {
	mysql_real_connect(
		_mysql_handle,
		_host.c_str(),
		_username.c_str(),
		_password.c_str(),
		_database.c_str(),
		3306,
		nullptr, 
		0
	);

	return mysql_errno(_mysql_handle);
}

uint ue_store_mysql::close() {
	mysql_close(_mysql_handle);
	return mysql_errno(_mysql_handle);
}

bool ue_store_mysql::get_ue_ctx(uint64_t ssid, hss_ue_ctx_t *ctx) {
	// Assumption is failure
	bool success = false;

	// Build the query
	std::string query = "SELECT `imsi`, `name`, `auth`, `key_identifier`, `op_type`, `op`, `opc`, `amf`, `sqn`, `qci`, `ip_alloc` FROM `user` WHERE `imsi` = ";
	query += std::to_string(ssid);

	// Perform the query
	int err = mysql_query(_mysql_handle, query.c_str());
	// Fast fail if the query failed
	if(err) { return false; }

	// Try to get the result
	MYSQL_RES * result = mysql_store_result(_mysql_handle);

	// If there is a result...
	if(result != nullptr) {
		
		// Get the number of rows, which should be one
		if(mysql_num_rows(result) == 1) {

			// Get the row, and the field count
			MYSQL_ROW row = mysql_fetch_row(result);
			uint num_fields = mysql_num_fields(result);

			// There should be 11 fields
			if(num_fields == 11) {
				// Get Lengths
				unsigned long *lengths = lengths = mysql_fetch_lengths(result);
				
				// Get IMSI
				ctx->imsi = std::stoull(row[0]);

				// Get Name
				ctx->name = std::string(row[1]);

				// Get Auth Type
				if(strcmp("xor",row[2]) == 0) { ctx->algo = HSS_ALGO_XOR; }
				if(strcmp("mil",row[2]) == 0) { ctx->algo = HSS_ALGO_MILENAGE; }

				// Get KI
				memcpy(ctx->key, (const char*)row[3], SRSEPC_HSS_UE_STORE_MYSQL_MIN_OF(lengths[3], 16));

				// Get OP / OPC Type
				ctx->op_configured = (strcmp("opc",row[4]) == 0);

				// Get OP/OPC
				memcpy(ctx->op, (const char*)row[5], SRSEPC_HSS_UE_STORE_MYSQL_MIN_OF(lengths[5], 16));
				memcpy(ctx->opc, (const char*)row[6], SRSEPC_HSS_UE_STORE_MYSQL_MIN_OF(lengths[6], 16));

				// Get AMF
				memcpy(ctx->amf, (const char*)row[7], SRSEPC_HSS_UE_STORE_MYSQL_MIN_OF(lengths[7], 2));

				// Get SQN
				memcpy(ctx->sqn, (const char*)row[8], SRSEPC_HSS_UE_STORE_MYSQL_MIN_OF(lengths[8], 6));

				// Get QCI
				ctx->qci = atoi(row[9]);

				// Get Assigned IP, or mark dynamic
				ctx->static_ip_addr = std::string(row[10]);

				// // Debug
				// for(uint i = 0; i < num_fields; i++) {
				//   printf("[%.*s](%d) ", (int) lengths[i], row[i] ? row[i] : "NULL", lengths[i]);
				// }
				// printf("\n");
			}
		} 

		// Free the result
		mysql_free_result(result);
	} 

	return success;
}

}