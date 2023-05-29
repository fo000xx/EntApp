# EntApp
An application to track entertainment content that has been consumed by the user/they would like to in the future.
It'll track Film, TV, Games & Books with some standard fields (title, genre, rating etc).
The data will be stored in a redis-like app that communicates to the client using TCP.
    
## TODO:
### Books
* Take input from the user and save to a data structure (map of structs)
    - Use "Author: Title" as a key
    - Clear cin stream to make sure previous entries cannot invalidate future
* Take input from the user and display a book
* Take input from a user and allow a book entry to be edited.
* Save to a csv file for long-term storage in-case server is interupted
    - Run on a separate thread every X seconds, and when an entry is added/edited/deleted.
