#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include "Games.h"

GameMap::GameMap()
{
    loadGames();
}

void GameMap::addGame(std::vector<std::string>& rawGameData)
{
    Game::mGameData gameData;
    gameData.gameTitle = rawGameData[2];
    gameData.gameGenre = rawGameData[3];
    gameData.platform = rawGameData[4];
    gameData.rating = std::stoi(rawGameData[5]);
    gameData.isMultiplayer = [](std::string rawGameData[6]) -> bool {
            return (rawGameData[6] == "1") ? true : false;
        };
    gameData.isPlayed = [](std::string rawGameData[7]) -> bool {
            return (rawGameData[7] == "1") ? true : false;
        };
    gameData.isOwned = [](std::string rawGameData[8]) -> bool {
            return (rawGameData[8] == "1") ? true : false;
        };

    std::size_t key{ generateKey(gameData.gameTitle) };

    auto search = gameDataMap.find(key);
    if (search == gameDataMap.end()) {
        gameDataMap.insert({key, gameData});
    }
    else {
        gameDataMap[key] = gameData;
    }
}

std::string GameMap::viewGame(const std::string& title)
{
    std::string returnString{};

    auto foundGameData{ findGame(title) };
    if (foundGameData != std::end(gameDataMap)) {
        returnString = (foundGameData->second.gameTitle + ','
        + foundGameData->second.gameGenre + ','
        + foundGameData->second.platform + ','
        + std::to_string(foundGameData->second.rating) + ','
        + std::to_string(foundGameData->second.isMultiplayer) + ','
        + std::to_string(foundGameData->second.isPlayed) + ','
        + std::to_string(foundGameData->second.isOwned) + ',');
    }
    else {
        returnString = "Game not found";
    }

    return returnString;
}

void GameMap::saveGames()
{
    std::ofstream gameFile;
    try {
    gameFile.open("gameData.csv");
    if (!gameFile.is_open()) {
        throw std::runtime_error("could not open file.");
    }
    } catch (const std::exception& exception) {
        std::cout << "Unable to save gameData.csv " << exception.what() 
            << "Any new entries are at risk of not being backed-up\n";
    }
    
    for (auto game : gameDataMap) {
        gameFile << game;
    }
    gameFile.close();
}

std::unordered_map<std::size_t, Game::mGameData>::iterator GameMap::findGame(const std::string& title)
{
    std::size_t key{ generateKey(title) };
    auto search = gameDataMap.find(key);
    if (search != gameDataMap.end()) {
        return search;
    }  
    
    return std::end(gameDataMap);
}

std::size_t GameMap::generateKey(const std::string& title)
{
    std::size_t originalHash{ std::hash<std::string>{}(title)};

    std::string hashString{ std::to_string(originalHash) };
    std::string truncHashString{ hashString.substr(0,9) };
    int truncatedHash{ std::stoi(truncHashString) };

    return truncatedHash;
}

void GameMap::convertLower(std::string& s)
{
    std::transform(s.begin(), s.end(), s.begin(),
    [](char c){ return std::tolower(c); });
}

void GameMap::loadGames()
{
    std::ifstream gameFile;
    try {
    gameFile.open("gameData.csv");
    if (!gameFile.is_open()) {
        throw std::runtime_error("could not open file.");
    }
    } catch (const std::exception& exception) {
        std::cout << "Unable to load gameData.csv " << exception.what() 
            << "Any data saved in long-term storage is not present.\n";
    }
    
    std::string dataLine;
    while(std::getline(gameFile, dataLine)) {
        std::istringstream inStringStream(dataLine);
        std::string keyString;     
   
        if (std::getline(inStringStream, keyString, ',')) {
            std::size_t key{ static_cast<std::size_t>(std::stoi(keyString)) };
            std::string inGameTitle, inGameGenre, inPlatform, inRating,
                inIsMultiplayer, inIsPlayed, inIsOwned;
            if (std::getline(inStringStream, inGameTitle, ',') && 
                std::getline(inStringStream, inGameGenre, ',') &&
                std::getline(inStringStream, inPlatform, ',') &&
                std::getline(inStringStream, inRating, ',') &&
                std::getline(inStringStream, inIsMultiplayer, ',') &&
                std::getline(inStringStream, inIsPlayed, ',') &&
                std::getline(inStringStream, inIsOwned, ',')) {
                    Game::mGameData gameDataStruct;
                    gameDataStruct.gameTitle = inGameTitle;
                    gameDataStruct.gameGenre = inGameGenre;
                    gameDataStruct.platform = inPlatform;
                    gameDataStruct.rating = std::stoi(inRating);
                    gameDataStruct.isMultiplayer = (inIsMultiplayer == "1");
                    gameDataStruct.isPlayed = (inIsPlayed == "1");
                    gameDataStruct.isOwned = (inIsOwned == "1");

                gameDataMap.insert({key, gameDataStruct});    
            }
        }
    }
}

void GameMap::deleteGame(const std::string& title)
{
    auto foundBookData{ findGame(title) };
    if (foundBookData != std::end(gameDataMap)) {
        gameDataMap.erase(foundBookData);
        return;
    }
}

std::ostream& operator<<(std::ostream& out, std::pair<std::size_t, Game::mGameData> gameDataPair)
{
    out << gameDataPair.first << ',' << gameDataPair.second.gameTitle << ',' << gameDataPair.second.gameGenre
        << ',' << gameDataPair.second.platform << ',' << gameDataPair.second.rating 
        << ',' << gameDataPair.second.isMultiplayer << ',' << gameDataPair.second.isPlayed 
        << ',' << gameDataPair.second.isOwned << '\n';

    return out;
}