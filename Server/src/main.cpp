#include "Server.h"

int main(int argc, char* argv[]) {
    try {
        boost::asio::io_context io_context;

        // Load SSL certificates
        boost::asio::ssl::context ssl_context(boost::asio::ssl::context::sslv23);

        Server s(io_context, 443, ssl_context); // Use port 443 for HTTPS
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
