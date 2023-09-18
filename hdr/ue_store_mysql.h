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

#ifndef SRSEPC_HSS_UE_STORE_MYSQL_H
#define SRSEPC_HSS_UE_STORE_MYSQL_H

#include <cstring>
#include <iostream>
#include <string>

#include "ue_store.h"

extern "C" {
#include "mysql.h"
}

namespace srsepc {

class ue_store_mysql : public ue_store
{
public:
  ue_store_mysql(std::string host, std::string database, std::string username, std::string password);
  ~ue_store_mysql();

  uint init();
  uint close();

  bool get_ue_ctx(uint64_t ssid, hss_ue_ctx_t* ctx);

private:
  std::string _host;
  std::string _database;
  std::string _username;
  std::string _password;

  MYSQL* _mysql_handle;
};

} // namespace srsepc

#endif // SRSEPC_HSS_UE_STORE_MYSQL