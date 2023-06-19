#ifndef SERVER_H
#define SERVER_H

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/bind/bind.hpp>
#include "Connection.h"
#include "Book.h"
#include "Games.h"
#include "Screens.h"

using namespace boost::asio::ip;

class tcpServer
{
public:
    tcpServer(int portNum, boost::asio::io_context& ioContext)
        : mIOContext{ ioContext }
        , mAcceptor{ ioContext, tcp::endpoint(tcp::v4(), portNum)}

    {
        startAccept();
    }

    BookMap mBooks;
    ScreenMap mScreens;
    GameMap mGames;

private:
    void startAccept();
    void handleAccept(tcpConnection::shrdPtr newConnection, const boost::system::error_code& error);

    boost::asio::io_context& mIOContext;
    tcp::acceptor mAcceptor;
};

#endif