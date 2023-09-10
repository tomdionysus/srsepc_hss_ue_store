#include "user_store_mysql.h"

int main() {
  UserStore *store = new UserStore("localhost","srsepc","root",nullptr);


  uint err = store->init();
  if(err!=0) store->printErr(err);

  err = store->close();
  if(err!=0) store->printErr(err);

  delete store;
}