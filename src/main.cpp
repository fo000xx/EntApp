#include "databaseCommon.h"
#include <iostream>

int main() {
  DatabaseCommon dB{};
  sqlite3 *entAppDB{dB.connectToDatabase()};
  if (nullptr == entAppDB) {
    std::cerr << "nullptr returned, connection failed.\n";
  }
  // user input
  int x{};
  std::cin >> x;

  // read from DB
  dB.readFromDatabase(entAppDB);

  // Write to DB

  // Close DB Connection
  int y{};
  std::cin >> y;

  dB.endDBConnection(entAppDB);

  return 0;
}
