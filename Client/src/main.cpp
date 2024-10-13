#include "Client.h"

int main(int argc, char* argv[]) {
    try {
        boost::asio::io_context io_context;

        // Create SSL context
        boost::asio::ssl::context ssl_context(boost::asio::ssl::context::sslv23);
        ssl_context.set_options(boost::asio::ssl::context::default_workarounds);
        ssl_context.load_verify_file("~/keys/crt.crt"); // Provide your CA certificate path here

        Client c(io_context, ssl_context, "localhost", "443");
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }
    return 0;
}
