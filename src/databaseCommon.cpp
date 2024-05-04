#include "databaseCommon.h"
#include <iostream>
#include <sqlite3.h>

sqlite3 *DatabaseCommon::connectToDatabase() {
  sqlite3 *database{};
  int connection{};
  if (sqlite3_open("EntApp.db", &database)) {
    std::cout << "Succesfully connected to the DB\n";
    return database;
  }
  std::cout << "Failed to connect to the DB\n";
  return nullptr;
}

int DatabaseCommon::endDBConnection(sqlite3 *database) {
  std::cout << "Closing connection\n";
  return sqlite3_close(database);
}

int DatabaseCommon::readFromDatabase(sqlite3 *database) {
  const char *sql{}; // sql statement
  const char *errmsg{};

  // sqlite3_exec(database, sql, printQueryResults, 0, &errmsg);
}

int DatabaseCommon::printQueryResults(void *, int, char **, char **) {
  // do something to print the results here.
}
