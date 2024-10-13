#include "Session.h"

void Session::run() {
    do_ssl_handshake();
}

// Perform SSL handshake
void Session::do_ssl_handshake() {
    auto self(shared_from_this());
    m_ssl_socket.async_handshake(boost::asio::ssl::stream_base::server,
        [this, self](boost::system::error_code ec) {
            if (!ec) {
                wait_for_request();
            } else {
                std::cerr << "Handshake error: " << ec.message() << std::endl;
            }
        });
}

// Wait for incoming requests
void Session::wait_for_request() {
    auto self(shared_from_this());
    boost::asio::async_read_until(m_ssl_socket, m_buffer, "\0",
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                std::string data{ std::istreambuf_iterator<char>(&m_buffer), std::istreambuf_iterator<char>() };
                std::cout << "Received request: " << data << std::endl;
                wait_for_request();  // Continue waiting for more requests
            } else {
                std::cout << "Error: " << ec.message() << std::endl;
            }
        });
}