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

#ifndef SRSEPC_HSS_UE_STORE_CSV_H
#define SRSEPC_HSS_UE_STORE_CSV_H

#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "ue_store.h"

namespace srsepc {

class ue_store_csv : public ue_store
{
public:
  ue_store_csv(std::string filename);
  ~ue_store_csv();

  uint init();
  uint close();

  bool get_ue_ctx(uint64_t ssid, hss_ue_ctx_t* ctx);

private:
  std::string _filename;

  std::map<uint64_t, hss_ue_ctx_t> _ue_subscriber;
};

} // namespace srsepc

#endif // SRSEPC_HSS_UE_STORE_CSV