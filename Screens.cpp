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

void ScreenMap::addScreen()
{
    Screen::mScreenData screenData;
    std::cout << "To add a TV/Film, please provide the following details:\n Title: ";
    takeUserInput(screenData.title);
    std::cout << "Type (TV/Film - beware this field is case sensitive): ";
    takeUserInput(screenData.type);
    std::cout << "Rating: ";
    takeUserInput(screenData.rating);
    std::cout << "isWatched (1/0): ";
    takeUserInput(screenData.isWatched);

    std::size_t key{ generateKey(screenData.title, screenData.type) };

    screenDataMap.insert({key, screenData});
}

void ScreenMap::viewScreens()
{
    bool userReattempt{ 1 };
    while (userReattempt) {
        auto foundScreenData{ findScreen() };
        if (foundScreenData != std::end(screenDataMap)) {
            std::cout << foundScreenData->second;
            return;
        }
        else {
            userReattempt = askReattempt();
        }
    }
}

void ScreenMap::editScreen()
{
    auto foundScreenData{ findScreen() };
    if (foundScreenData != std::end(screenDataMap)) {
        std::string userFieldChoice{};
        std::string userValueChoice{};
        std::cout << "Which field would you like to edit? ";
        std::cin >> userFieldChoice;
        std::cout << "What would you like to change " << userFieldChoice << " to? ";
        std::cin >> userValueChoice;

        convertLower(userFieldChoice);

        if (userFieldChoice == "title") {
            std::cout << "Title updated from: " << foundScreenData->second.title
                << " to: " << userValueChoice;
            foundScreenData->second.title = userValueChoice;
            
            auto nodeHandler = screenDataMap.extract(foundScreenData);
            nodeHandler.key() = generateKey(foundScreenData->second.title, foundScreenData->second.type);
            screenDataMap.insert(std::move(nodeHandler));
        }
        else if (userFieldChoice == "type") {
            std::cout << "Type updated from: " << foundScreenData->second.type
                << " to: " << userValueChoice;
            foundScreenData->second.type = userValueChoice;
            
            auto nodeHandler = screenDataMap.extract(foundScreenData);
            nodeHandler.key() = generateKey(foundScreenData->second.title, foundScreenData->second.type);
            screenDataMap.insert(std::move(nodeHandler));
        }
        else if (userFieldChoice == "rating") {
            std::cout << "Rating updated from: " << foundScreenData->second.rating
                << " to: " << userValueChoice;
            foundScreenData->second.rating = std::stoi(userValueChoice);
        }
        else if (userFieldChoice == "isRead") {
            std::cout << "isRead updated from: " << foundScreenData->second.isWatched
                << " to: " << userValueChoice;
            foundScreenData->second.isWatched = [](std::string userValueChoice) -> bool {
                return (userValueChoice == "1") ? true : false;
            };
        }
        std::cout << '\n';
    }
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

std::unordered_map<std::size_t, Screen::mScreenData>::iterator ScreenMap::findScreen()
{
    bool userReattempt{ 1 };
    while (userReattempt) { 
        std::cout << "Enter the title of the TV/Film you want to find: ";
        std::string userInputTitle;
        std::cin >> userInputTitle;
        std::cout << "and the type (TV/Film - this is case sensitive): ";
        std::string userInputType;
        std::cin >> userInputType;

        std::size_t key{ generateKey(userInputTitle, userInputType) };
    
        auto search = screenDataMap.find(key);
        if (search != screenDataMap.end()) {
            return search;
        }
        else {
            std::cout << "Screen not found.\n";
            userReattempt = askReattempt();
        }
    }    
    
    return std::end(screenDataMap);
}
 
bool ScreenMap::askReattempt()
{
    bool reattemptResponse{ 0 };
    std::cout << "Would you like to reattempt entry? (1/0) ";
    std::cin >> reattemptResponse;
    return reattemptResponse;
}

std::size_t ScreenMap::generateKey(const std::string& title, const std::string& type)
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

std::ostream& operator<<(std::ostream& out, const Screen::mScreenData& screenData)
{
    out << screenData.title << "\nType: " << screenData.type
        << "\nRating: " << screenData.rating << "\nisWatched: " << screenData.isWatched << '\n';

    return out;
}

std::ostream& operator<<(std::ostream& out, std::pair<std::size_t, Screen::mScreenData> screenDataPair)
{
    out << screenDataPair.first << ',' << screenDataPair.second.title << ',' << screenDataPair.second.type
        << ',' << screenDataPair.second.rating << ',' << screenDataPair.second.isWatched << '\n';

    return out;
}