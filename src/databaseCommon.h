#ifndef CONNECTION_H
#define CONNECTION_H

#include <sqlite3.h>

class DatabaseCommon {
public:
  sqlite3 *connectToDatabase();
  int endDBConnection(sqlite3 *Database);
  int readFromDatabase(sqlite3 *Database);

private:
  int printQueryResults(void *, int, char **, char **);
};

#endif
