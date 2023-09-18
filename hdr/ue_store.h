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

#ifndef SRSEPC_HSS_UE_STORE_H
#define SRSEPC_HSS_UE_STORE_H

#include <iostream>
#include <string>

#define SRSEPC_HSS_UE_STORE_CLAMP(a, b) (a < b ? a : b)

namespace srsepc {

enum hss_auth_algo { HSS_ALGO_XOR, HSS_ALGO_MILENAGE };

struct hss_ue_ctx_t {
  // Members
  std::string        name;
  uint64_t           imsi;
  enum hss_auth_algo algo;
  uint8_t            key[16];
  bool               op_configured;
  uint8_t            op[16];
  uint8_t            opc[16];
  uint8_t            amf[2];
  uint8_t            sqn[6];
  uint16_t           qci;
  uint8_t            last_rand[16];
  std::string        static_ip_addr;

  // Helper getters/setters
  void set_sqn(const uint8_t* sqn_);
  void set_last_rand(const uint8_t* rand_);
  void get_last_rand(uint8_t* rand_);
};

class ue_store
{
public:
  virtual ~ue_store(){};

  virtual uint init()  = 0;
  virtual uint close() = 0;

  virtual bool get_ue_ctx(uint64_t ssid, hss_ue_ctx_t* ctx) = 0;
};

} // namespace srsepc

#endif // SRSEPC_HSS_UE_STORE