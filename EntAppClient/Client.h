#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>
#include <boost/asio/io_service.hpp>
#include <iostream>
#include <string>
#include <string_view>

using namespace boost::asio::ip;

class Client
{
public:
    Client(std::string& ipAddr, int portNum, boost::asio::io_context& ioContext); 

    void receiveConfirmation(boost::system::error_code& error);
    void sendMessage();
    void userInputMessage();

private:
    std::string mIPAddr;
    int mPortNum;
    tcp::socket mSocket;
    boost::asio::streambuf mReceiveBuffer;
    std::string mUserInput{ "defaultHello\n" };
};

#endif