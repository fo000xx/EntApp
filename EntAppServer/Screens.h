#ifndef SCREENS_H
#define SCREENS_H

#include <string>
#include <limits>
#include <unordered_map>
#include <vector>

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
    friend std::ostream& operator<<(std::ostream& out, std::pair<std::size_t,  Screen::mScreenData> screenData);
};

class ScreenMap
{
public:
    ScreenMap();

    void addScreen(std::vector<std::string>& rawScreenData);
    std::string viewScreens(const std::string& type, const std::string& title);
    void saveScreens();
    void deleteScreen(const std::string& type, const std::string& title);

private:
    std::unordered_map<std::size_t, Screen::mScreenData> screenDataMap{};

    std::unordered_map<std::size_t, Screen::mScreenData>::iterator findScreen(const std::string& type, const std::string& title);
    std::size_t generateKey(const std::string& type, const std::string& title);
    void convertLower(std::string& s);
    void loadScreens();
};

#endif