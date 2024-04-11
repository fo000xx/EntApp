#include "databaseCommon.h"
#include <sqlite3.h>

int connectToDatabase() {
  // connect to SQLite DB
  sqlite3 *Database{};
  int connection{};
  connection = sqlite3_open("EntApp.db", &Database);

  sqlite3_close(Database);

  return 1;
}
