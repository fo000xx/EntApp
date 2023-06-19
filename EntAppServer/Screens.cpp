#include <cstdlib>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <string>
#include <cmath>
#include "Screens.h"

ScreenMap::ScreenMap()
{
  loadScreens(); 
}

void ScreenMap::addScreen(std::vector<std::string>& rawScreenData)
{
    Screen::mScreenData screenData;
    screenData.title = rawScreenData[3];
    screenData.type = rawScreenData[2];
    screenData.rating = std::stoi(rawScreenData[4]);
    screenData.isWatched = [](std::string rawScreenData[5]) -> bool {
            return (rawScreenData[7] == "1") ? true : false;
        };

    std::size_t key{ generateKey(screenData.type, screenData.title) };
    
    auto search = screenDataMap.find(key);
    if (search == screenDataMap.end()) {
        screenDataMap.insert({key, screenData});
    }
    else {
        screenDataMap[key] = screenData;
    }
}

std::string ScreenMap::viewScreens(const std::string& type, const std::string& title)
{
    std::string returnString{};
    
    auto foundScreenData{ findScreen(type, title) };
    if (foundScreenData != std::end(screenDataMap)) {
        returnString = (foundScreenData->second.title + ','
            + foundScreenData->second.type + ','
            + std::to_string(foundScreenData->second.rating) + ','
            + std::to_string(foundScreenData->second.isWatched));
    }
    else {
        returnString = "TV/Film not found";
    }

    return returnString;
}

void ScreenMap::saveScreens()
{
    std::ofstream screenFile;
    try {
    screenFile.open("screenData.csv");
    if (!screenFile.is_open()) {
        throw std::runtime_error("could not open file.");
    }
    } catch (const std::exception& exception) {
        std::cout << "Unable to save screenData.csv " << exception.what() 
            << "Any new entries are at risk of not being backed-up\n";
    }
    
    for (auto screen : screenDataMap) {
        screenFile << screen;
    }
    screenFile.close();
}

std::unordered_map<std::size_t, Screen::mScreenData>::iterator ScreenMap::findScreen(const std::string& type, const std::string& title)
{
    std::size_t key{ generateKey(type, title) };
    
    auto search = screenDataMap.find(key);
    if (search != screenDataMap.end()) {
        return search;
    }
    
    return std::end(screenDataMap);
}

std::size_t ScreenMap::generateKey(const std::string& type, const std::string& title)
{
    std::string key(type + title);
    std::size_t originalHash{ std::hash<std::string>{}(key)};

    std::string hashString{ std::to_string(originalHash) };
    std::string truncHashString{ hashString.substr(0,9) };
    int truncatedHash{ std::stoi(truncHashString) };
    
    return truncatedHash;
}

void ScreenMap::convertLower(std::string& s)
{
    std::transform(s.begin(), s.end(), s.begin(),
    [](char c){ return std::tolower(c); });
}

void ScreenMap::loadScreens()
{
    std::ifstream screenFile;
    try {
    screenFile.open("screenData.csv");
    if (!screenFile.is_open()) {
        throw std::runtime_error("could not open file.");
    }
    } catch (const std::exception& exception) {
        std::cout << "Unable to load screenData.csv " << exception.what() 
            << "Any data saved in long-term storage is not present.\n";
    }
    std::string dataLine;
    while(std::getline(screenFile, dataLine)) {
        std::istringstream inStringStream(dataLine);
        std::string keyString;  

        if (std::getline(inStringStream, keyString, ',')) {
            std::size_t key{ static_cast<std::size_t>(std::stoi(keyString)) };
            std::string inTitle, inType, inRating, inIsWatched;
            if (std::getline(inStringStream, inTitle, ',') && 
                std::getline(inStringStream, inType, ',') &&
                std::getline(inStringStream, inRating, ',') &&
                std::getline(inStringStream, inIsWatched, ',')) {
                    Screen::mScreenData screenDataStruct;
                    screenDataStruct.title = inTitle;
                    screenDataStruct.type = inType;
                    screenDataStruct.rating = std::stoi(inRating);
                    screenDataStruct.isWatched = (inIsWatched == "1");

                screenDataMap.insert({key, screenDataStruct});    
            }
        }
    }
}

void ScreenMap::deleteScreen(const std::string& type, const std::string& title)
{
    auto foundScreenData{ findScreen(type, title) };
    if (foundScreenData != std::end(screenDataMap)) {
        screenDataMap.erase(foundScreenData);
        return;
    }
}

std::ostream& operator<<(std::ostream& out, std::pair<std::size_t, Screen::mScreenData> screenDataPair)
{
    out << screenDataPair.first << ',' << screenDataPair.second.title << ',' << screenDataPair.second.type
        << ',' << screenDataPair.second.rating << ',' << screenDataPair.second.isWatched << '\n';

    return out;
}