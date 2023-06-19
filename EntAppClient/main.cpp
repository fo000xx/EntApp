#include <boost/asio.hpp>
#include <iostream>
#include "Client.h"

using namespace boost::asio::ip;

int main()
{
    std::string ipAddr("127.0.0.1");
    boost::asio::io_context ioContext;
    Client client(ipAddr, 1234, ioContext);

    //opening prompt > book, screen, game
    client.gatherData();
    //select book
    //get, set, del
    //get -> input key
    //send key, return struct
    //print struct

    client.sendMessage();

    return 0;
}