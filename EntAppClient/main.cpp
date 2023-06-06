#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <iostream>
#include <string_view>
#include "Client.h"

using namespace boost::asio::ip;

int main()
{
    std::string ipAddr("127.0.0.1");
    boost::asio::io_context ioContext;
    Client client(ipAddr, 1234, ioContext);

    client.userInputMessage();
    client.sendMessage();

    return 0;
}