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
    std::cout << "Read? (1/0): ";
    takeUserInput(bookData.isRead);

    std::string key(bookData.bookAuthor + ": " + bookData.bookTitle);

    bookDataMap.insert({key, bookData});
}

void BookMap::viewBook()
{
    std::cout << "Enter the title of the book you want to view: ";
    std::string userInputTitle;
    std::cin >> userInputTitle;
    std::cout << "and the author? ";
    std::string userInputAuthor;
    std::cin >> userInputAuthor;

    std::string key(userInputAuthor + ": " + userInputTitle);

    if (auto search = bookDataMap.find(key); search != bookDataMap.end()) {
        std::cout << search->second.bookTitle;
    }
    else {
        std::cout << "Book not found.\n";
    }
    
}

std::ostream& operator<<(std::ostream& out, Book::mBookData& bookData)
{
    out << bookData.bookAuthor << ": " << bookData.bookTitle
        << "\n Series: " << bookData.series << "\n Genre: " << bookData.genre
        << "\n Rating: " << bookData.rating << "\n Read?: " << bookData.isRead;

    return out;
}