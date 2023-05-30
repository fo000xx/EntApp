#include <cstdlib>
#include <iostream>
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

    std::string key(bookData.bookAuthor + ": " + bookData.bookTitle);

    bookDataMap.insert({key, bookData});
}

void BookMap::viewBook()
{
    bool userReattempt{ 1 };
    while (userReattempt) {
        auto foundBookData{ findBook() };
        if (foundBookData != nullptr) {
            std::cout << *foundBookData;
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
    if (foundBookData != nullptr) {
        std::string userFieldChoice{};
        std::string userValueChoice{};
        std::cout << "Which field would you like to edit? ";
        std::cin >> userFieldChoice;
        std::cout << "What would you like to change " << userFieldChoice << " to? ";
        std::cin >> userValueChoice;
        if (userFieldChoice == "Title") {
            std::cout << "Title updated from: " << foundBookData->bookTitle
                << " to: " << userValueChoice;
            foundBookData->bookTitle = userValueChoice;
        }
        else if (userFieldChoice == "Author") {
            std::cout << "Author updated from: " << foundBookData->bookAuthor
                << " to: " << userValueChoice;
            foundBookData->bookAuthor = userValueChoice;
        }
        else if (userFieldChoice == "Series") {
            std::cout << "Series updated from:" << foundBookData->series
                << " to: " << userValueChoice;
            foundBookData->series = userValueChoice;
        }
        else if (userFieldChoice == "Genre") {
            std::cout << "Genre updated from: " << foundBookData->genre
                << " to: " << userValueChoice;
            foundBookData->genre = userValueChoice;
        }
        else if (userFieldChoice == "Rating") {
            std::cout << "Rating updated from: " << foundBookData->rating
                << " to: " << userValueChoice;
            foundBookData->rating = std::stoi(userValueChoice);
        }
        else if (userFieldChoice == "isRead") {
            std::cout << "isRead updated from: " << foundBookData->isRead
                << " to: " << userValueChoice;
            foundBookData->isRead = [](std::string userValueChoice) -> bool {
                return (userValueChoice == "1") ? true : false;
            };
        }
        std::cout << '\n';
    }
}

const std::unique_ptr<Book::mBookData> BookMap::findBook()
{
    bool userReattempt{ 1 };
    while (userReattempt) { 
        std::cout << "Enter the title of the book you want to find: ";
        std::string userInputTitle;
        std::cin >> userInputTitle;
        std::cout << "and the author: ";
        std::string userInputAuthor;
        std::cin >> userInputAuthor;
    
        std::string key(userInputAuthor + ": " + userInputTitle);
    
        auto search = bookDataMap.find(key);
        if (search != bookDataMap.end()) {
            std::unique_ptr<Book::mBookData> foundBookData{ std::make_unique<Book::mBookData>(search->second) };
            return foundBookData;
        }
        else {
            std::cout << "Book not found.\n";
            userReattempt = askReattempt();
        }
    }    
    
    return nullptr;
}

bool BookMap::askReattempt()
{
    bool reattemptResponse{ 0 };
    std::cout << "Would you like to reattempt entry? (1/0) ";
    std::cin >> reattemptResponse;
    return reattemptResponse;
}

std::ostream& operator<<(std::ostream& out, const Book::mBookData& bookData)
{
    out << bookData.bookAuthor << ": " << bookData.bookTitle
        << "\n Series: " << bookData.series << "\n Genre: " << bookData.genre
        << "\n Rating: " << bookData.rating << "\n isRead: " << bookData.isRead << '\n';

    return out;
}