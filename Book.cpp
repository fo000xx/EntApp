#include <cstdlib>
#include <exception>
#include <iostream>
#include <fstream>
#include <sstream>
#include <functional>
#include <string>
#include "Book.h"

BookMap::BookMap()
{
  loadBooks();  
}

void BookMap::addBook()
{
    Book::mBookData bookData;
    std::cout << "To add a book, please provide the following details:\n Title: ";
    takeUserInput(bookData.bookTitle);
    std::cout << "Author: ";
    takeUserInput(bookData.bookAuthor);
    std::cout << "Series: ";
    takeUserInput(bookData.series);
    std::cout << "Genre: ";
    takeUserInput(bookData.genre);
    std::cout << "Rating: ";
    takeUserInput(bookData.rating);
    std::cout << "isRead (1/0): ";
    takeUserInput(bookData.isRead);

    std::size_t key{ generateKey(bookData.bookTitle, bookData.bookAuthor) };

    bookDataMap.insert({key, bookData});
}

void BookMap::viewBook()
{
    bool userReattempt{ 1 };
    while (userReattempt) {
        auto foundBookData{ findBook() };
        if (foundBookData != nullptr) {
            std::cout << foundBookData->second;
            return;
        }
        else {
            userReattempt = askReattempt();
        }
    }
}

void BookMap::editBook()
{
    auto foundBookData{ findBook() };
    if (foundBookData != std::end(bookDataMap)) {
        std::string userFieldChoice{};
        std::string userValueChoice{};
        std::cout << "Which field would you like to edit? ";
        std::cin >> userFieldChoice;
        std::cout << "What would you like to change " << userFieldChoice << " to? ";
        std::cin >> userValueChoice;

        convertLower(userFieldChoice);

        if (userFieldChoice == "title") {
            std::cout << "Title updated from: " << foundBookData->second.bookTitle
                << " to: " << userValueChoice;
            foundBookData->second.bookTitle = userValueChoice;
            
            auto nodeHandler = bookDataMap.extract(foundBookData);
            nodeHandler.key() = generateKey(foundBookData->second.bookTitle, foundBookData->second.bookAuthor);
            bookDataMap.insert(std::move(nodeHandler));
        }
        else if (userFieldChoice == "author") {
            std::cout << "Author updated from: " << foundBookData->second.bookAuthor
                << " to: " << userValueChoice;
            foundBookData->second.bookAuthor = userValueChoice;
            
            auto nodeHandler = bookDataMap.extract(foundBookData);
            nodeHandler.key() = generateKey(foundBookData->second.bookTitle, foundBookData->second.bookAuthor);
            bookDataMap.insert(std::move(nodeHandler));
        }
        else if (userFieldChoice == "series") {
            std::cout << "Series updated from:" << foundBookData->second.series
                << " to: " << userValueChoice;
            foundBookData->second.series = userValueChoice;
        }
        else if (userFieldChoice == "genre") {
            std::cout << "Genre updated from: " << foundBookData->second.genre
                << " to: " << userValueChoice;
            foundBookData->second.genre = userValueChoice;
        }
        else if (userFieldChoice == "rating") {
            std::cout << "Rating updated from: " << foundBookData->second.rating
                << " to: " << userValueChoice;
            foundBookData->second.rating = std::stoi(userValueChoice);
        }
        else if (userFieldChoice == "isRead") {
            std::cout << "isRead updated from: " << foundBookData->second.isRead
                << " to: " << userValueChoice;
            foundBookData->second.isRead = [](std::string userValueChoice) -> bool {
                return (userValueChoice == "1") ? true : false;
            };
        }
        std::cout << '\n';
    }
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

std::unordered_map<std::size_t, Book::mBookData>::iterator BookMap::findBook()
{
    bool userReattempt{ 1 };
    while (userReattempt) { 
        std::cout << "Enter the title of the book you want to find: ";
        std::string userInputTitle;
        std::cin >> userInputTitle;
        std::cout << "and the author: ";
        std::string userInputAuthor;
        std::cin >> userInputAuthor;

        std::size_t key{ generateKey(userInputTitle, userInputAuthor) };
    
        auto search = bookDataMap.find(key);
        if (search != bookDataMap.end()) {
            return search;
        }
        else {
            std::cout << "Book not found.\n";
            userReattempt = askReattempt();
        }
    }    
    
    return std::end(bookDataMap);
}
 
bool BookMap::askReattempt()
{
    bool reattemptResponse{ 0 };
    std::cout << "Would you like to reattempt entry? (1/0) ";
    std::cin >> reattemptResponse;
    return reattemptResponse;
}

std::size_t BookMap::generateKey(const std::string& title, const std::string& author)
{
    std::string key(author + ": " + title);
    std::size_t originalHash{ std::hash<std::string>{}(key)};

    std::size_t truncatedHash{ originalHash / 100'000'000'000 };
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

std::ostream& operator<<(std::ostream& out, const Book::mBookData& bookData)
{
    out << bookData.bookAuthor << ": " << bookData.bookTitle
        << "\n Series: " << bookData.series << "\n Genre: " << bookData.genre
        << "\n Rating: " << bookData.rating << "\n isRead: " << bookData.isRead << '\n';

    return out;
}

std::ostream& operator<<(std::ostream& out, std::pair<std::size_t, Book::mBookData> bookDataPair)
{
    out << bookDataPair.first << ',' << bookDataPair.second.bookTitle << ',' << bookDataPair.second.bookAuthor
        << ',' << bookDataPair.second.series << ',' << bookDataPair.second.genre << ',' << bookDataPair.second.rating
        << ',' << bookDataPair.second.isRead << '\n';

    return out;
}