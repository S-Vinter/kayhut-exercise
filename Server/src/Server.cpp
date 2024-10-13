#include "Server.h"

// Accept new connections
void Server::do_accept() {
    m_acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
            std::cout << "Creating session for: "
                        << socket.remote_endpoint().address().to_string()
                        << ":" << socket.remote_endpoint().port() << '\n';

            // Create a new session for the connected socket
            std::make_shared<Session>(std::move(socket), m_ssl_context)->run();
        } else {
            std::cout << "Accept error: " << ec.message() << std::endl;
        }
        do_accept(); // Continue accepting new connections
    });
}
