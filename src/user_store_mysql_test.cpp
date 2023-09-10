#include <gtest/gtest.h>

#include "user_store_mysql.h"

using namespace std;

// Instantiate, check 
TEST(FreemapTest, NewDestroy) {
  UserStore *store = new UserStore("localhost","srsepc","root",nullptr);

  // delete store;
}