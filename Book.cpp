#include <cstdlib>
#include <iostream>
#include <functional>
#include "Book.h"

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
        if (userFieldChoice == "Title") {
            std::cout << "Title updated from: " << foundBookData->second.bookTitle
                << " to: " << userValueChoice;
            foundBookData->second.bookTitle = userValueChoice;
            
            auto nodeHandler = bookDataMap.extract(foundBookData);
            nodeHandler.key() = generateKey(foundBookData->second.bookTitle, foundBookData->second.bookAuthor);
            bookDataMap.insert(std::move(nodeHandler));
        }
        else if (userFieldChoice == "Author") {
            std::cout << "Author updated from: " << foundBookData->second.bookAuthor
                << " to: " << userValueChoice;
            foundBookData->second.bookAuthor = userValueChoice;
            
            auto nodeHandler = bookDataMap.extract(foundBookData);
            nodeHandler.key() = generateKey(foundBookData->second.bookTitle, foundBookData->second.bookAuthor);
            bookDataMap.insert(std::move(nodeHandler));
        }
        else if (userFieldChoice == "Series") {
            std::cout << "Series updated from:" << foundBookData->second.series
                << " to: " << userValueChoice;
            foundBookData->second.series = userValueChoice;
        }
        else if (userFieldChoice == "Genre") {
            std::cout << "Genre updated from: " << foundBookData->second.genre
                << " to: " << userValueChoice;
            foundBookData->second.genre = userValueChoice;
        }
        else if (userFieldChoice == "Rating") {
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
    return std::hash<std::string>{}(key);
}

std::ostream& operator<<(std::ostream& out, const Book::mBookData& bookData)
{
    out << bookData.bookAuthor << ": " << bookData.bookTitle
        << "\n Series: " << bookData.series << "\n Genre: " << bookData.genre
        << "\n Rating: " << bookData.rating << "\n isRead: " << bookData.isRead << '\n';

    return out;
}