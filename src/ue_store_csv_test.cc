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

#include "hdr/ue_store_csv.h"

using namespace std;
using namespace srsepc;

// Instantiate, check
TEST(UEStoreCSV, NewDestroy)
{
  ue_store* store = new ue_store_csv("../data/ue_subscriber.csv");

  delete store;
}

// Load Single Row
TEST(UEStoreCSV, SingleRow)
{
  ue_store* store = new ue_store_csv("../data/ue_subscriber.csv");

  EXPECT_EQ(store->init(), 0);

  hss_ue_ctx_t ctx;

  EXPECT_EQ(store->get_ue_ctx(1010123456780, &ctx), true);

  const uint8_t ki[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff};
  const uint8_t op[] = {0x63, 0xbf, 0xa5, 0x0e, 0xe6, 0x52, 0x33, 0x65, 0xff, 0x14, 0xc1, 0xf4, 0x5f, 0x88, 0x73, 0x7d};
  const uint8_t amf[] = {0x80, 0x00};
  const uint8_t sqn[] = {0x00, 0x00, 0x00, 0x00, 0x12, 0x34};

  EXPECT_EQ(ctx.imsi, 1010123456780);
  EXPECT_EQ("ue2", ctx.name);
  EXPECT_EQ(ctx.algo, HSS_ALGO_MILENAGE);
  EXPECT_EQ(*ki, *ctx.key);
  EXPECT_EQ(ctx.op_configured, true);
  EXPECT_EQ(*op, *ctx.op);
  EXPECT_EQ(*amf, *ctx.amf);
  EXPECT_EQ(*sqn, *ctx.sqn);
  EXPECT_EQ(ctx.qci, 7);
  EXPECT_EQ(ctx.static_ip_addr, "dynamic");

  EXPECT_EQ(store->close(), 0);

  delete store;
}

// Not Found
TEST(UEStoreCSV, NotFound)
{
  ue_store* store = new ue_store_csv("../data/ue_subscriber.csv");

  EXPECT_EQ(store->init(), 0);

  hss_ue_ctx_t ctx;

  EXPECT_EQ(store->get_ue_ctx(28347823748, &ctx), false);

  EXPECT_EQ(store->close(), 0);

  delete store;
}