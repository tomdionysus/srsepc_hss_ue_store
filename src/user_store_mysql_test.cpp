#include <gtest/gtest.h>

#include "user_store_mysql.h"

using namespace std;

// Instantiate, check 
TEST(FreemapTest, NewDestroy) {
	UserStore *store = new UserStore("localhost", "srsepc", "root", nullptr);

	delete store;
}

// Load Single Row
TEST(FreemapTest, SingleRow) {
	UserStore *store = new UserStore("localhost", "srsepc", "root", nullptr);

	EXPECT_EQ(store->init(), 0);

	user_context_t ctx;

	store->getUser(530302814353573, &ctx);

	const uint8_t ki[] = { 0x7E, 0x9B, 0xA6, 0x62, 0x5F, 0xD1, 0xA7, 0x2B, 0x48, 0xF0, 0xA6, 0x7A, 0xD5, 0xD5, 0x27, 0x54 };
	const uint8_t opopc[] = { 0x6b, 0x34, 0x44, 0xc5, 0x83, 0x5a, 0x5d, 0xf7, 0xd3, 0xad, 0xd5, 0x7e, 0x85, 0xb7, 0x70, 0xe3 };
	const uint8_t amf[] = { 0xFF, 0x55 };
	in_addr ipalloc; inet_aton("192.168.11.44", &ipalloc);

	EXPECT_EQ(ctx.imsi, 530302814353573);
	EXPECT_EQ(strcmp("Tom Cully", ctx.name), 0);
	EXPECT_EQ(ctx.auth, auth_type_mil);
	EXPECT_EQ(memcmp(ki, ctx.key_identifier, 16), 0);
	EXPECT_EQ(ctx.op, op_type_opc);
	EXPECT_EQ(memcmp(opopc, ctx.op_opc, 16), 0);
	EXPECT_EQ(memcmp(amf, ctx.amf, 2), 0);
	EXPECT_EQ(ctx.sqn, 255);
	EXPECT_EQ(ctx.qci, 1);
	EXPECT_EQ(ctx.dynamic_ip, false);
	EXPECT_EQ(memcmp(&ctx.ip_alloc, &ipalloc, 4),0);

	EXPECT_EQ(store->close(), 0);

	delete store;
}