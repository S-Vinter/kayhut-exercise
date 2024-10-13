#include "Server.h"

using boost::asio::ip::tcp;

void Session::run() {
    m_socket.async_handshake(boost::asio::ssl::stream_base::server,
        [self = shared_from_this()](const boost::system::error_code& ec) {
            if (!ec) {
                self->wait_for_request();
            } else {
                std::cerr << "Handshake error: " << ec.message() << std::endl;
            }
        });
}

void Session::wait_for_request() {
    auto self(shared_from_this());
    boost::asio::async_read_until(m_socket, m_buffer, "\r\n\r\n",
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                std::string data{
                    std::istreambuf_iterator<char>(&m_buffer),
                    std::istreambuf_iterator<char>() 
                };
                std::cout << "Received request:\n" << data << std::endl;

                // Send response
                std::string response = "HTTP/1.1 200 OK\r\nContent-Length: 0\r\n\r\n";
                boost::asio::async_write(m_socket, boost::asio::buffer(response),
                    [self](boost::system::error_code ec, std::size_t /*length*/) {
                        if (ec) {
                            std::cerr << "Write error: " << ec.message() << std::endl;
                        }
                    });
            } else {
                std::cout << "Read error: " << ec.message() << std::endl;
            }
        });
}

void Server::do_accept() {
    m_acceptor.async_accept([this](boost::system::error_code ec, tcp::socket socket) {
        if (!ec) {
            std::cout << "Creating session from: "
                        << socket.remote_endpoint().address().to_string()
                        << ":" << socket.remote_endpoint().port() << '\n';

            std::make_shared<Session>(std::move(socket), m_ssl_context)->run();
        } else {
            std::cout << "Accept error: " << ec.message() << std::endl;
        }
        do_accept();
    });
}
