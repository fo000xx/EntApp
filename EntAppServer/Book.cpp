#include <cstdlib>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <string>
#include <cmath>
#include "Book.h"

BookMap::BookMap()
{
  loadBooks();  
}

void BookMap::addBook(std::vector<std::string>& rawBookData)
{
    Book::mBookData bookData;
    bookData.bookTitle = rawBookData[3];
    bookData.bookAuthor = rawBookData[2];
    bookData.series = rawBookData[4];
    bookData.genre = rawBookData[5];
    bookData.rating = std::stoi(rawBookData[6]);
    bookData.isRead = [](std::string rawBookData[7]) -> bool {
            return (rawBookData[7] == "1") ? true : false;
        };

    std::size_t key{ generateKey(bookData.bookAuthor, bookData.bookTitle) };

    auto search = bookDataMap.find(key);
    if (search == bookDataMap.end()) {
        bookDataMap.insert({key, bookData});
    }
    else {
        bookDataMap[key] = bookData;
    }
}

std::string BookMap::viewBook(const std::string& author, const std::string& title)
{
    std::string returnString{};

    auto foundBookData{ findBook(author, title) };
    if (foundBookData != std::end(bookDataMap)) {
        returnString = (foundBookData->second.bookAuthor + ',' 
            + foundBookData->second.bookTitle + ','
            + foundBookData->second.series + ','
            + foundBookData->second.genre + ','
            + std::to_string(foundBookData->second.rating) + ','
            + std::to_string(foundBookData->second.isRead));
    }
    else {
        returnString = "Book not found";
    }

    return returnString;
}

void BookMap::saveBooks()
{
    std::ofstream bookFile;
    try {
    bookFile.open("bookData.csv");
    if (!bookFile.is_open()) {
        throw std::runtime_error("could not open file.");
    }
    } catch (const std::exception& exception) {
        std::cout << "Unable to save bookData.csv " << exception.what() 
            << "Any new entries are at risk of not being backed-up\n";
    }
    
    for (auto book : bookDataMap) {
        bookFile << book;
    }
    bookFile.close();
}

std::unordered_map<std::size_t, Book::mBookData>::iterator BookMap::findBook(const std::string& author, const std::string& title)
{
    
    std::size_t key{ generateKey(author, title) };
    
    auto search = bookDataMap.find(key);
    if (search != bookDataMap.end()) {
        return search;
    }
    
    return std::end(bookDataMap);
}

std::size_t BookMap::generateKey(const std::string& author, const std::string& title)
{
    std::string key(author + ": " + title);
    std::size_t originalHash{ std::hash<std::string>{}(key)};

    std::string hashString{ std::to_string(originalHash) };
    std::string truncHashString{ hashString.substr(0,9) };
    int truncatedHash{ std::stoi(truncHashString) };

    return truncatedHash;
}

void BookMap::convertLower(std::string& s)
{
    std::transform(s.begin(), s.end(), s.begin(),
    [](char c){ return std::tolower(c); });
}

void BookMap::loadBooks()
{
    std::ifstream bookFile;
    try {
    bookFile.open("bookData.csv");
    if (!bookFile.is_open()) {
        throw std::runtime_error("could not open file.");
    }
    } catch (const std::exception& exception) {
        std::cout << "Unable to load bookData.csv " << exception.what() 
            << "Any data saved in long-term storage is not present.\n";
    }
    
    std::string dataLine;
    while(std::getline(bookFile, dataLine)) {
        std::istringstream inStringStream(dataLine);
        std::string keyString;     
   
        if (std::getline(inStringStream, keyString, ',')) {
            std::size_t key{ static_cast<std::size_t>(std::stoi(keyString)) };
            std::string inBookTitle, inBookAuthor, inSeries, inGenre, inRating, inIsRead;
            if (std::getline(inStringStream, inBookTitle, ',') && 
                std::getline(inStringStream, inBookAuthor, ',') &&
                std::getline(inStringStream, inSeries, ',') &&
                std::getline(inStringStream, inGenre, ',') &&
                std::getline(inStringStream, inRating, ',') &&
                std::getline(inStringStream, inIsRead, ',')) {
                    Book::mBookData bookDataStruct;
                    bookDataStruct.bookTitle = inBookTitle;
                    bookDataStruct.bookAuthor = inBookAuthor;
                    bookDataStruct.series = inSeries;
                    bookDataStruct.genre = inGenre;
                    bookDataStruct.rating = std::stoi(inRating);
                    bookDataStruct.isRead = (inIsRead == "1");

                bookDataMap.insert({key, bookDataStruct});    
            }
        }
    }
}

void BookMap::deleteBook(const std::string& author, const std::string& title)
{
    auto foundBookData{ findBook(author, title) };
    if (foundBookData != std::end(bookDataMap)) {
        bookDataMap.erase(foundBookData);
        return;
    }
}

std::ostream& operator<<(std::ostream& out, std::pair<std::size_t, Book::mBookData> bookDataPair)
{
    out << bookDataPair.first << ',' << bookDataPair.second.bookTitle << ',' << bookDataPair.second.bookAuthor
        << ',' << bookDataPair.second.series << ',' << bookDataPair.second.genre << ',' << bookDataPair.second.rating
        << ',' << bookDataPair.second.isRead << '\n';

    return out;
}