# EntApp
An application to track entertainment content that has been consumed by the user/they would like to in the future.
It'll track Film, TV, Games & Books with some standard fields (title, genre, rating etc).
The data will be stored in a redis-like app that communicates to the client using TCP.

# Notes
* Hash is truncated, due to high numbers and relatively low entries, collision chance is still low. However there is no mechanism for dealing with collisions currently.
* When moving to Client/Server build, operator<< overloads will need to be removed from server and placed into client.

## TODO:
### Books
* COMPLETE Take input from the user and save to a data structure (map of structs)
    - Use "Author: Title" as a key
    - Clear cin stream to make sure previous entries cannot invalidate future
* COMPLETE Take input from the user and display a book
* COMPLETE Take input from a user and allow a book entry to be edited.
* COMPLETE Add a tolower function that will allow users to input whichever case they want (for field titles, field values will be case sensitive)
* COMPLETE Save to a csv file for long-term storage in-case server is interupted
* COMPLETE Edit find function to return optional pointer
    - Instead return an iterator to the value, or std::end() if there is no value
* COMPLETE Load from a csv file that's used for long-term storage
    - wrap load into the class constructor
* COMPLETE Add an error check when opening the file for saving/loading

### Games
* COMPLETE Add game objects, similar mechanisms as above

### TV/Film
* COMPLETE Add screen objects

### Other
* Tidy up README to include proper instructions etc.
* Add input validation to bool and int fields for editing/adding.
* Build fully into TCPServer code, with access through a client only.
* Run save on a separate thread every X seconds, and when an entry is added/edited/deleted.
    - make save a private method once done.
* Add a mechanism for dealing with key collisions in the data structs