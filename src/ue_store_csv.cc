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

#include <iostream> 
#include <string>
#include <map>

#include "hdr/ue_store_csv.h"

using namespace std;

namespace srsepc {

ue_store_csv::ue_store_csv(std::string filename) {
	_filename = filename; 
}

ue_store_csv::~ue_store_csv() {
}

uint ue_store_csv::init() {
	// Load from CSV File
	return 0;
}

uint ue_store_csv::close() {
	// Nothing to do
	return 0;
}

bool ue_store_csv::get_ue_ctx(uint64_t ssid, hss_ue_ctx_t *ctx) {
	std::map<uint64_t, hss_ue_ctx_t>::iterator it;
	it = _user.find(ssid);
	if (it != _user.end()) return false;
	*ctx = it->second;
	return true;
}

}