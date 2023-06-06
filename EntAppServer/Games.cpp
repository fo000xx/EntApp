#include <cstdlib>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <string>
#include <cmath>
#include "Games.h"

GameMap::GameMap()
{
    loadGames();
}

void GameMap::addGame()
{
    Game::mGameData gameData;
    std::cout << "To add a game, please provide the following details:\n Title: ";
    takeUserInput(gameData.gameTitle);
    std::cout << "Genre: ";
    takeUserInput(gameData.gameGenre);
    std::cout << "Platform: ";
    takeUserInput(gameData.platform);
    std::cout << "Rating: ";
    takeUserInput(gameData.rating);
    std::cout << "isMultiplayer (1/0)";
    takeUserInput(gameData.isMultiplayer);
    std::cout << "isPlayed (1/0)";
    takeUserInput(gameData.isPlayed);
    std::cout << "isOwned (1/0)";
    takeUserInput(gameData.isOwned);

    std::size_t key{ generateKey(gameData.gameTitle) };

    gameDataMap.insert({key, gameData});
}

void GameMap::viewGame()
{
    bool userReattempt{ 1 };
    while (userReattempt) {
        auto foundGameData{ findGame() };
        if (foundGameData != std::end(gameDataMap)) {
            std::cout << foundGameData->second;
            return;
        }
        else {
            userReattempt = askReattempt();
        }
    }
}

void GameMap::editGame()
{
    auto foundGameData{ findGame() };
    if (foundGameData != std::end(gameDataMap)) {
        std::string userFieldChoice{};
        std::string userValueChoice{};
        std::cout << "Which field would you like to edit? ";
        std::cin >> userFieldChoice;
        std::cout << "What would you like to change " << userFieldChoice << " to? ";
        std::cin >> userValueChoice;

        convertLower(userFieldChoice);

        if (userFieldChoice == "title") {
            std::cout << "Title updated from: " << foundGameData->second.gameTitle
                << " to " << userValueChoice;
            foundGameData->second.gameTitle = userValueChoice;

            auto nodeHandler = gameDataMap.extract(foundGameData);
            nodeHandler.key() = generateKey(foundGameData->second.gameTitle);
            gameDataMap.insert(std::move(nodeHandler));
        }
        else if (userFieldChoice == "genre") {
            std::cout << "Genre updated from: " << foundGameData->second.gameGenre
                << " to " << userValueChoice;
            foundGameData->second.gameGenre = userValueChoice;
        }
        else if (userFieldChoice == "platform") {
            std::cout << "Platform updated from: " << foundGameData->second.platform
                << " to " << userValueChoice;
            foundGameData->second.platform = userValueChoice;
        }
        else if (userFieldChoice == "rating") {
            std::cout << "Platform updated from: " << foundGameData->second.rating
                << " to " << userValueChoice;
            foundGameData->second.rating = std::stoi(userValueChoice);
        }
        else if (userFieldChoice == "isMultiplayer") {
            std::cout << "isRead updated from: " << foundGameData->second.isMultiplayer
                << " to: " << userValueChoice;
            foundGameData->second.isMultiplayer = [](std::string userValueChoice) -> bool {
                return (userValueChoice == "1") ? true : false;
            };
        }
        else if (userFieldChoice == "isPlayed") {
            std::cout << "isRead updated from: " << foundGameData->second.isPlayed
                << " to: " << userValueChoice;
            foundGameData->second.isPlayed = [](std::string userValueChoice) -> bool {
                return (userValueChoice == "1") ? true : false;
            };
        }
        else if (userFieldChoice == "isOwned") {
            std::cout << "isRead updated from: " << foundGameData->second.isOwned
                << " to: " << userValueChoice;
            foundGameData->second.isOwned = [](std::string userValueChoice) -> bool {
                return (userValueChoice == "1") ? true : false;
            };
        }
        std::cout << '\n';
    }
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

std::unordered_map<std::size_t, Game::mGameData>::iterator GameMap::findGame()
{
    bool userReattempt{ 1 };
    while (userReattempt) { 
        std::cout << "Enter the title of the game you want to find: ";
        std::string userInputTitle;
        std::cin >> userInputTitle;

        std::size_t key{ generateKey(userInputTitle) };
    
        auto search = gameDataMap.find(key);
        if (search != gameDataMap.end()) {
            return search;
        }
        else {
            std::cout << "Game not found.\n";
            userReattempt = askReattempt();
        }
    }    
    
    return std::end(gameDataMap);
}

bool GameMap::askReattempt()
{
    bool reattemptResponse{ 0 };
    std::cout << "Would you like to reattempt entry? (1/0) ";
    std::cin >> reattemptResponse;
    return reattemptResponse;
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

std::ostream& operator<<(std::ostream& out, const Game::mGameData& gameData)
{
    out << gameData.gameTitle << "\nGenre: " << gameData.gameGenre
        << "\nPlatform: " << gameData.platform << "\nRating: " << gameData.rating
        << "\nisMultiplayer:  " << gameData.isMultiplayer 
        << "\nisPlayed: " << gameData.isPlayed
        << "\nisOwned: " << gameData.isOwned << '\n';

    return out;
}

std::ostream& operator<<(std::ostream& out, std::pair<std::size_t, Game::mGameData> gameDataPair)
{
    out << gameDataPair.first << ',' << gameDataPair.second.gameTitle << ',' << gameDataPair.second.gameGenre
        << ',' << gameDataPair.second.platform << ',' << gameDataPair.second.rating 
        << ',' << gameDataPair.second.isMultiplayer << ',' << gameDataPair.second.isPlayed 
        << ',' << gameDataPair.second.isOwned << '\n';

    return out;
}