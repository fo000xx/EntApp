#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <limits>
#include <iostream>
#include <unordered_map>
#include <vector>

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
    friend std::ostream& operator<<(std::ostream& out, std::pair<std::size_t, Book::mBookData> bookDataPair);
};

class BookMap
{
public:
    BookMap();
    
    void addBook(std::vector<std::string>& rawBookData);
    std::string viewBook(const std::string& author, const std::string& title);
    void editBook(const std::string& author, const std::string& title);
    void saveBooks();
    void deleteBook(const std::string& author, const std::string& title);

private:
    std::unordered_map<std::size_t, Book::mBookData> bookDataMap{};
    
    std::unordered_map<std::size_t, Book::mBookData>::iterator findBook(const std::string& author, const std::string& title);
    std::size_t generateKey(const std::string& title, const std::string& author);
    void convertLower(std::string& s);
    void loadBooks();
};

#endif