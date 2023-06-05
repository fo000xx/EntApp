#include <iostream>
#include "Book.h"

int main() 
{
    BookMap bookData{};
    //bookData.loadBooks();
    bookData.addBook();
    bookData.saveBooks();
    //bookData.loadBooks();
    //bookData.addBook();
    //bookData.saveBooks();

    return 0;
}
