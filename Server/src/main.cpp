#include "Server.h"

int main(int argc, char* argv[]) {
    try {
        boost::asio::io_context io_context;

        // Load SSL certificates
        boost::asio::ssl::context ssl_context(boost::asio::ssl::context::sslv23);

        // Load server's certificate and private key
        ssl_context.set_options(boost::asio::ssl::context::default_workarounds | boost::asio::ssl::context::no_sslv2);
        ssl_context.use_certificate_chain_file("/server.crt");
        ssl_context.use_private_key_file("/server.key", boost::asio::ssl::context::pem);
        ssl_context.load_verify_file("/ca.crt");
        // ssl_context.use_certificate_chain_file("/keys/server.crt");
        // ssl_context.use_private_key_file("/keys/server.key", boost::asio::ssl::context::pem);
        // ssl_context.load_verify_file("/keys/ca.crt");

        Server s(io_context, 443, ssl_context); // Use port 443 for HTTPS
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
