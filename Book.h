#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <limits>
#include <iostream>
#include <memory>
#include <unordered_map>

class Book
{
public:      
    struct mBookData
    {
        std::string bookTitle;
        std::string bookAuthor;
        std::string series;
        std::string genre;
        int rating;
        bool isRead;
    };

private:
    friend std::ostream& operator<<(std::ostream& out, const Book::mBookData& bookDataMap);
};

class BookMap //eventually constructor function will read from CSV and store data in memory, similar to REDIS
{
public:
    void addBook();
    void viewBook();
    void editBook();

private:
    std::unordered_map<std::size_t, Book::mBookData> bookDataMap{};
    
    std::unordered_map<std::size_t, Book::mBookData>::iterator findBook();
    bool askReattempt();
    std::size_t generateKey(const std::string& title, const std::string& author);
    
    template<typename T>
    void takeUserInput(T& valueToUpdate)
    {
        std::cin.clear();
        std::cin >> valueToUpdate;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    friend std::ostream& operator<<(std::ostream& out, const Book::mBookData& bookDataMap);
};

#endif