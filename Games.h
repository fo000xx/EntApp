#ifndef GAMES_H
#define GAMES_H

#include <string>
#include <limits>
#include <iostream>
#include <unordered_map>

class Game
{
public:
    struct mGameData
    {
        std::string gameTitle;
        std::string gameGenre;
        std::string platform;
        int rating;
        bool isMultiplayer;
        bool isPlayed;
        bool isOwned;
    };

private:
    friend std::ostream& operator<<(std::ostream& out, const Game::mGameData& gameData);
    friend std::ostream& operator<<(std::ostream& out, std::pair<std::size_t, Game::mGameData> gameDataPair);

};

class GameMap
{
public:
    GameMap();

    void addGame();
    void viewGame();
    void editGame();
    void saveGames();

private:
    std::unordered_map<std::size_t, Game::mGameData> gameDataMap{};

    std::unordered_map<std::size_t, Game::mGameData>::iterator findGame();
    bool askReattempt();
    std::size_t generateKey(const std::string& title);
    void convertLower(std::string& s);
    void loadGames();

    template<typename T>
    void takeUserInput(T& valueToUpdate)
    {
        std::cin.clear();
        std::cin >> valueToUpdate;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    friend std::ostream& operator<<(std::ostream& out, const Game::mGameData& bookData);
    friend std::ostream& operator<<(std::ostream& out, std::pair<std::size_t, Game::mGameData> bookDataPair);

};

#endif