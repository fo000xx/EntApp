#include <boost/asio.hpp>
#include <iostream>
#include "Server.h"

using namespace boost::asio::ip;

int main()
{    
    try {
    boost::asio::io_context ioContext;
    tcpServer server(1234, ioContext);
    ioContext.run();
    } catch (std::exception& exception) {
        std::cout << exception.what() << '\n';
    }

    return 0;
}