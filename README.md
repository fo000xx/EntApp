# EntApp
An application to track entertainment content that has been consumed by the user/they would like to in the future.
It'll track Film, TV, Games & Books with some standard fields (title, genre, rating etc).
The data will be stored in a redis-like app that communicates to the client using TCP.

# Notes
Hash is truncated, due to high numbers and relatively low entries, collision chance is still low. However there is no mechanism for dealing with collisions currently.

## TODO:
### Books
* COMPLETE Take input from the user and save to a data structure (map of structs)
    - Use "Author: Title" as a key
    - Clear cin stream to make sure previous entries cannot invalidate future
* COMPLETE Take input from the user and display a book
* COMPLETE Take input from a user and allow a book entry to be edited.
* COMPLETE Add a tolower function that will allow users to input whichever case they want (for field titles, field values will be case sensitive)
* COMPLETE Save to a csv file for long-term storage in-case server is interupted
    - **OUTSTANDING** Run on a separate thread every X seconds, and when an entry is added/edited/deleted.
        - To be built into functioning server, rather than book/TV/Film/Game entries.
* COMPLETE Edit find function to return optional pointer
    - Instead return an iterator to the value, or std::end() if there is no value
* Only allow int entry for rating and bool rating for isRead
* COMPLETE Load from a csv file that's used for long-term storage
    - wrap load into the class constructor
* COMPLETE Add an error check when opening the file for saving/loading