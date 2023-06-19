#include <boost/asio/placeholders.hpp>
#include <iostream>
#include "Connection.h"
#include "Server.h"

using shrdPtr = std::shared_ptr<tcpConnection>;

shrdPtr tcpConnection::createConnection(boost::asio::io_context& ioContext, tcpServer& server)
{
    return shrdPtr(new tcpConnection(ioContext, server));
}

void tcpConnection::startConn()
{
    readIncoming();
    
    confirmConnection();
}

void tcpConnection::confirmConnection()
{
    std::string_view ackRes{ "Command Received\n"};
    boost::asio::async_write(mSocket, boost::asio::buffer(ackRes), 
        boost::bind(&tcpConnection::writeHandler, shared_from_this(),
        boost::asio::placeholders::error));
}

void tcpConnection::readIncoming()
{   
    boost::asio::async_read_until(mSocket, mReceiveBuffer, '\n', 
            boost::bind(&tcpConnection::readHandler, shared_from_this(), 
            boost::asio::placeholders::error));
}

void tcpConnection::readHandler(const boost::system::error_code& error)
{
    if (!error) {
        mReceivedMsg = boost::asio::buffer_cast<const char*>(mReceiveBuffer.data());
        parseAndActionCommand();
    }
    else {
        std::cout << error.message() << '\n';
    }
}

void tcpConnection::writeOutgoing()
{
    boost::asio::async_write(mSocket, boost::asio::buffer(mResponse), 
        boost::bind(&tcpConnection::writeHandler, shared_from_this(),
        boost::asio::placeholders::error));
}

void tcpConnection::writeHandler(const boost::system::error_code& errorMessage)
{
    if (errorMessage) {
        std::cout << errorMessage << '\n';
    }
}

void tcpConnection::parseAndActionCommand()
{
    std::stringstream receivedStringStream{ mReceivedMsg };
    std::string token{};

    while (std::getline(receivedStringStream, token, ',')) {
        mSplitStrings.push_back(token);
    }

    if (mSplitStrings[0] == "books") {
        manageBooks();
    }
    else if (mSplitStrings[0] == "screens") {
        //manageScreens();
    }
    else if (mSplitStrings[0] == "games") {
        //manageGames();
    }

    for (auto elem : mSplitStrings) {
        std::cout << elem << "||";
    }
}

void tcpConnection::manageBooks()
{
    if (mSplitStrings[1] == "get") {
        mResponse = mServer.mBooks.viewBook(mSplitStrings[2], mSplitStrings[3]);
    }
    if (mSplitStrings[1] == "set") {
        //if book doesn't exist, add new
        //if book exists, edit old
        mServer.mBooks.addBook(mSplitStrings);
    }
    if (mSplitStrings[1] == "del") {
        mServer.mBooks.deleteBook(mSplitStrings[2], mSplitStrings[3]);
    }

    writeOutgoing();
}

/*
//probably should be refactored if this was to scale up.
void tcpConnection::parseAndActionCommand()
{
    std::stringstream cmdStream{ mReceivedMsg };
    std::string command{}, key{}, value{};

    cmdStream >> command >> key;
    if (command == "set") {
        cmdStream >> value;
        if (!key.empty() && !value.empty()) {
            gDemoMap::DemoMap.insert({key, value});
            mResponse = ("Values added");
        }
        else {
            mResponse = "Invalid format, please try set KEY VALUE";
        }
    }
    else if (command == "get") {
        auto keyExists {gDemoMap::DemoMap.find(key)};
        if (keyExists != gDemoMap::DemoMap.end()) {
            mResponse = (keyExists->first + " " + keyExists->second);
        }
        else {
           mResponse = ("Key not found");
        }
    }
    else if (command == "del") {
        auto keyExists {gDemoMap::DemoMap.find(key)};
        if (keyExists != gDemoMap::DemoMap.end()) {
            gDemoMap::DemoMap.erase(key);
            mResponse = ("key/value deleted");
        }
        else { 
            mResponse = ("key not found");
        } 
    }
    else {
        mResponse = ("invalid command");
    }
    
    writeOutgoing(); //message needs to be sent AFTER actions are completed.
    //for testing
    for (auto elem : gDemoMap::DemoMap) { std::cout << elem.first << " " << elem.second << '\n'; }
}
*/