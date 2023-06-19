#ifndef GAMES_H
#define GAMES_H

#include <string>
#include <limits>
#include <vector>
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
    friend std::ostream& operator<<(std::ostream& out, std::pair<std::size_t, Game::mGameData> gameDataPair);

};

class GameMap
{
public:
    GameMap();

    void addGame(std::vector<std::string>& rawGameData);
    std::string viewGame(const std::string& title);
    void saveGames();
    void deleteGame(const std::string& title);

private:
    std::unordered_map<std::size_t, Game::mGameData> gameDataMap{};

    std::unordered_map<std::size_t, Game::mGameData>::iterator findGame(const std::string& title);
    std::size_t generateKey(const std::string& title);
    void convertLower(std::string& s);
    void loadGames();

    friend std::ostream& operator<<(std::ostream& out, std::pair<std::size_t, Game::mGameData> bookDataPair);

};

#endif