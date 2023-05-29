#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <limits>
#include <iostream>
#include <unordered_map>

class Book
{
public:   
    std::string mBookTitleAuthor;
    
    struct mBookData
    {
        std::string bookTitle;
        std::string bookAuthor;
        std::string series;
        std::string genre;
        int rating;
        bool isRead;
    }; 
};

class BookMap //eventually constructor function will read from CSV and store data in memory, similar to REDIS
{
public:
    void addBook();
    void viewBook();

private:
    std::unordered_map<std::string, Book::mBookData> bookDataMap{};
    
    template<typename T>
    void takeUserInput(T& valueToUpdate)
    {
        std::cin.clear();
        std::cin >> valueToUpdate;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    friend std::ostream& operator<<(std::ostream& out, Book::mBookData& bookDataMap);
};

#endif