#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <limits>
#include <iostream>
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
    friend std::ostream& operator<<(std::ostream& out, const Book::mBookData& bookData);
    friend std::ostream& operator<<(std::ostream& out, std::pair<std::size_t, Book::mBookData> bookDataPair);
};

class BookMap
{
public:
    BookMap();
    
    void addBook();
    void viewBook();
    void editBook();
    void saveBooks();

private:
    std::unordered_map<std::size_t, Book::mBookData> bookDataMap{};
    
    std::unordered_map<std::size_t, Book::mBookData>::iterator findBook();
    bool askReattempt();
    std::size_t generateKey(const std::string& title, const std::string& author);
    void convertLower(std::string& s);
    void loadBooks();
    
    template<typename T>
    void takeUserInput(T& valueToUpdate)
    {
        std::cin.clear();
        std::cin >> valueToUpdate;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    friend std::ostream& operator<<(std::ostream& out, const Book::mBookData& bookData);
    friend std::ostream& operator<<(std::ostream& out, std::pair<std::size_t, Book::mBookData> bookDataPair);
};

#endif