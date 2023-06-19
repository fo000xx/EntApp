#ifndef CLIENT_H
#define CLIENT_H

#include <boost/asio.hpp>
#include <string>

using namespace boost::asio::ip;

class Client
{
public:
    Client(std::string& ipAddr, int portNum, boost::asio::io_context& ioContext); 

    void receiveConfirmation(boost::system::error_code& error);
    void sendMessage();
    void gatherData();

private:
    std::string mIPAddr;
    int mPortNum;
    tcp::socket mSocket;
    boost::asio::streambuf mReceiveBuffer;
    std::string mOutMessage;

    std::string getContentType();
    void convertLower(std::string& stringToConvert);
    std::string getAction();
    std::string getContentKey(const std::string& contentType);
    std::string getContentData(const std::string& contentType);

};

#endif