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

#include "hdr/ue_store_psql.h"

using namespace std;

namespace srsepc {

ue_store_psql::ue_store_psql(std::string conninfo)
{
  _conninfo = conninfo;
}

ue_store_psql::~ue_store_psql() {}

uint ue_store_psql::init()
{
  /* Make a connection to the database */
  _conn = PQconnectdb(_conninfo.c_str());

  /* Check to see that the backend connection was successfully made */
  if (PQstatus(_conn) != CONNECTION_OK) {
    fprintf(stderr, "%s", PQerrorMessage(_conn));
  }
}

uint ue_store_psql::close()
{
  PQfinish(_conn);
}

bool ue_store_psql::get_ue_ctx(uint64_t ssid, hss_ue_ctx_t* ctx)
{
  // Assumption is failure
  bool success = false;

  // Build the query
  std::string query = "SELECT `imsi`, `name`, `auth`, `key_identifier`, `op_type`, `op`, "
                      "`opc`, `amf`, `sqn`, `qci`, `ip_alloc` FROM `user` WHERE `imsi` = ";

  return success;
}

} // namespace srsepc