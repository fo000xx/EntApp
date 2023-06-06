#ifndef SCREENS_H
#define SCREENS_H

#include <string>
#include <limits>
#include <iostream>
#include <unordered_map>

class Screen
{
public:
    struct mScreenData
    {
        std::string title;
        std::string type;
        int rating;
        bool isWatched;
    };

private:
    friend std::ostream& operator<<(std::ostream& out, const Screen::mScreenData& screenData);
    friend std::ostream& operator<<(std::ostream& out, std::pair<std::size_t,  Screen::mScreenData> screenData);

};

class ScreenMap
{
public:
    ScreenMap();

    void addScreen();
    void viewScreens();
    void editScreen();
    void saveScreens();

private:
    std::unordered_map<std::size_t, Screen::mScreenData> screenDataMap{};

    std::unordered_map<std::size_t, Screen::mScreenData>::iterator findScreen();
    bool askReattempt();
    std::size_t generateKey(const std::string& title, const std::string& type);
    void convertLower(std::string& s);
    void loadScreens();

    template<typename T>
    void takeUserInput(T& valueToUpdate)
    {
        std::cin.clear();
        std::cin >> valueToUpdate;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    friend std::ostream& operator<<(std::ostream& out, const Screen::mScreenData& screenData);
    friend std::ostream& operator<<(std::ostream& out, std::pair<std::size_t, Screen::mScreenData> screenDataPair);

};

#endif