#include <iostream>
#include "Book.h"
#include "Games.h"
#include "Screens.h"

int main() 
{
    //BookMap bookData{};
    //GameMap gameData{};
    ScreenMap screenData{};
    screenData.addScreen();
    screenData.editScreen();
    screenData.viewScreens();
    screenData.saveScreens();

    return 0;
}
