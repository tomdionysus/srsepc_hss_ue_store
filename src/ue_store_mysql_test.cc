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

#include <gtest/gtest.h>

#include "hdr/ue_store_mysql.h"

using namespace std;
using namespace srsepc;

// Instantiate, check 
TEST(FreemapTest, NewDestroy) {
	ue_store *store = new ue_store_mysql("localhost", "srsepc", "root", "");

	delete store;
}

// Load Single Row
TEST(FreemapTest, SingleRow) {
	ue_store *store = new ue_store_mysql("localhost", "srsepc", "root", "");

	EXPECT_EQ(store->init(), 0);

	hss_ue_ctx_t ctx;

	store->get_ue_ctx(530302814353573, &ctx);

	const uint8_t ki[] = { 0x7E, 0x9B, 0xA6, 0x62, 0x5F, 0xD1, 0xA7, 0x2B, 0x48, 0xF0, 0xA6, 0x7A, 0xD5, 0xD5, 0x27, 0x54 };
	const uint8_t op[] = { 0x6b, 0x34, 0x44, 0xc5, 0x83, 0x5a, 0x5d, 0xf7, 0xd3, 0xad, 0xd5, 0x7e, 0x85, 0xb7, 0x70, 0xe3 };
	const uint8_t opc[] = { 0x8B, 0x5B, 0x5F, 0x24, 0x01, 0x7F, 0x41, 0x1B, 0xA8, 0xDE, 0x85, 0xF0, 0x3E, 0xA1, 0x64, 0x80 };
	const uint8_t amf[] = { 0x3F, 0x55 };
	const uint8_t sqn[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06 };

	EXPECT_EQ(ctx.imsi, 530302814353573);
	EXPECT_EQ("Tom Cully", ctx.name);
	EXPECT_EQ(ctx.algo, HSS_ALGO_MILENAGE);
	EXPECT_EQ(*ki, *ctx.key);
	EXPECT_EQ(ctx.op_configured, true);
	EXPECT_EQ(*op, *ctx.op);
	EXPECT_EQ(*opc, *ctx.opc);
	EXPECT_EQ(*amf, *ctx.amf);
	EXPECT_EQ(*sqn, *ctx.sqn);
	EXPECT_EQ(ctx.qci, 1);
	EXPECT_EQ(ctx.static_ip_addr, "192.168.11.44");

	EXPECT_EQ(store->close(), 0);

	delete store;
}