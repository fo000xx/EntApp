#include <iostream>
#include "Book.h"

int main() 
{
    BookMap bookData{};
    bookData.addBook();
    bookData.viewBook();
    bookData.editBook();
    bookData.viewBook();
    bookData.editBook();
    bookData.viewBook();
    return 0;
}