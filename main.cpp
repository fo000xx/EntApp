#include <iostream>
#include "Book.h"
#include "Games.h"

int main() 
{
    BookMap bookData{};
    GameMap gameData{};
    gameData.addGame();
    gameData.editGame();
    gameData.saveGames();

    return 0;
}
