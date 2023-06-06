#ifndef CONNECTION_H
#define CONNECTION_H

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/bind/bind.hpp>

class tcpServer;
using namespace boost::asio::ip;

class tcpConnection : public std::enable_shared_from_this<tcpConnection>
{
public:
    using shrdPtr = std::shared_ptr<tcpConnection>;

    static shrdPtr createConnection(boost::asio::io_context& ioContext, tcpServer& server);
    void startConn();
    tcp::socket& getSocket() { return mSocket; }

private:
    tcpConnection(boost::asio::io_context& ioContext, tcpServer& server)
        : mSocket(ioContext)
        , mServer{ server }
    {
    }

    void readIncoming();
    void readHandler(const boost::system::error_code& error);
    void confirmConnection();
    void parseAndActionCommand();
    void writeOutgoing();
    void writeHandler(const boost::system::error_code& errorMessage);

    tcp::socket mSocket;
    boost::asio::streambuf mReceiveBuffer;
    tcpServer& mServer;
    std::string mReceivedMsg;
    std::string_view mResponse;

};

#endif