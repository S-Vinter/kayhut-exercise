#include "Client.h"

int main(int argc, char* argv[]) {
    try {
        boost::asio::io_context io_context;

        // Create SSL context
        boost::asio::ssl::context ssl_context(boost::asio::ssl::context::sslv23);
        ssl_context.set_options(boost::asio::ssl::context::default_workarounds);
        ssl_context.load_verify_file("/ca.crt");

        // Load client's certificate and private key
        ssl_context.use_certificate_chain_file("/client.crt");
        ssl_context.use_private_key_file("/client.key", boost::asio::ssl::context::pem);

        Client c(io_context, ssl_context, "localhost", "443");
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
