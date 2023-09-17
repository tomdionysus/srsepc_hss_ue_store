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

#ifndef SRSEPC_HSS_UE_STORE_PSQL_H
#define SRSEPC_HSS_UE_STORE_PSQL_H

#include <iostream> 
#include <string>
#include <cstring>

#include "ue_store.h"

extern "C" {
	#include "libpq-fe.h"
}

#define SRSEPC_HSS_UE_STORE_PSQL_MIN_OF(a,b) (a < b ? a : b)

namespace srsepc {

class ue_store_psql : public ue_store {  
	public:
		ue_store_psql(std::string conninfo);
		~ue_store_psql();

		uint init();
		uint close();

		bool get_ue_ctx(uint64_t ssid, hss_ue_ctx_t *ctx);
	private:
		std::string _conninfo;

		PGconn *_conn;
};  

}

#endif // SRSEPC_HSS_UE_STORE_PSQL