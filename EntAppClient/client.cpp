#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include "Client.h"

Client::Client(std::string& ipAddr, int portNum, boost::asio::io_context& ioContext) 
    : mIPAddr{ ipAddr }
    , mPortNum{ portNum }
    , mSocket{ ioContext }
{
    mSocket.connect(tcp::endpoint(address::from_string(mIPAddr), mPortNum));
}

void Client::receiveConfirmation(boost::system::error_code& error)
{
    boost::asio::read(mSocket, mReceiveBuffer, boost::asio::transfer_all(), error);
    if (error && error != boost::asio::error::eof) {
        std::cout << "receive failed: " << error.message() << '\n';
    }
    else {
        std::string_view receivedMsg = boost::asio::buffer_cast<const char*>(mReceiveBuffer.data());
        std::cout << receivedMsg << '\n';
    }
}

void Client::sendMessage()
{
    boost::system::error_code sendError;
    boost::asio::write(mSocket, boost::asio::buffer(mOutMessage), sendError);

    if (!sendError) {
        std::cout << "Client sent command!\n";
    }
    else {
        std::cout << "send failed: " << sendError.message() << '\n';
    }

    receiveConfirmation(sendError);
}

void Client::gatherData()
{
    std::string contentType{ getContentType() };
    std::string requiredAction{ getAction() };
    
    std::string contentData{};
    if (requiredAction == "set") {
        contentData = getContentData(contentType);
    }
    else {
        contentData = getContentKey(contentType);
    }

    mOutMessage = (contentType + ',' + requiredAction + ',' + contentData + '\n');
}

void Client::convertLower(std::string& stringToConvert)
{
    std::transform(stringToConvert.begin(), stringToConvert.end(), stringToConvert.begin(),
    [](char c){ return std::tolower(c); });
}

std::string Client::getContentType()
{
    while (true) {
        std::cout << "Would you like to access Books, Screens or Games? ";
        std::string userTypeChoice{};
        std::cin >> userTypeChoice;
        convertLower(userTypeChoice);
        if (userTypeChoice == "books" || userTypeChoice == "screens" || userTypeChoice == "games") {
            return userTypeChoice;
        }
        else {
            std::cout << "Invalid entry, try again.";
        }
    }
}

std::string Client::getAction()
{
    while (true) {
        std::cout << "Would you like to access get, set or del? ";
        std::string userActionChoice{};
        std::cin >> userActionChoice;
        convertLower(userActionChoice);

        if (userActionChoice == "get" || userActionChoice == "set" || userActionChoice == "del") {
            return userActionChoice;
        }
        else {
            std::cout << "Invalid entry, try again.";
        }
    }  
}

std::string Client::getContentKey(const std::string& contentType)
{
    std::string rawKey{}; //commas are added to split out \n or other unwanted, lingering characters
    if (contentType == "books") {
        std::string author{};
        std::string title{};
        std::cout << "Please provide the author and title.\nAuthor: ";
        std::cin >> author;
        std::cout << "Title: ";
        std::cin >> title;
        
        rawKey = (author + ',' + title + ',');
    }

    if (contentType == "screens") {
        std::string type{};
        std::string title{};
        std::cout << "Please provide the type (TV/Film) and title.\nType: ";
        std::cin >> type;
        std::cout << "Title: ";
        std::cin >> title;

        rawKey = (type + ',' + title + ',');
    }

    return rawKey;
}

std::string Client::getContentData(const std::string& contentType)
{
    std::string finalData{};
    
    if (contentType == "books") {
        std::string author{};
        std::string title{};
        std::string series{};
        std::string genre{};
        std::string rating{};
        std::string isRead{};

        std::cout << "To add a book, please provide the following details:\n Author: ";
        std::cin >> author;
        
        std::cout << "Title: ";
        std::cin >> title;

        std::cout << "Series: ";
        std::cin >> series;
        
        std::cout << "Genre: ";
        std::cin >> genre;
        
        std::cout << "Rating (1-5): ";
        std::cin >> rating;
        
        std::cout << "isRead (1/0): ";
        std::cin >> isRead;

        finalData = (author + ',' + title + ',' + series + ',' + genre + ',' + rating + ',' + isRead);
    }

    if (contentType == "screens") {
        std::string type{};
        std::string title{};
        std::string rating{};
        std::string isWatched{};

        std::cout << "To add a screen, please provide the following details:\n Type (TV/Film): ";
        std::cin >> type;

        std::cout << "Title: ";
        std::cin >> title;

        std::cout << "Rating (1-5): ";
        std::cin >> rating;

        std::cout << "isWatched (1/0): ";
        std::cin >> isWatched;

        finalData = (type + ',' + title + ',' + rating + ',' + isWatched);
    }
    return finalData;
}