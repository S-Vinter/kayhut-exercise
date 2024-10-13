#pragma once

#include <memory>
#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
public:
    // Constructor takes a socket and an SSL context
    Session(tcp::socket socket, boost::asio::ssl::context& ctx)
        : m_ssl_socket(std::move(socket), ctx) {
        }

    void run();

private:
    // Perform SSL handshake
    void do_ssl_handshake();

    // Wait for incoming requests
    void wait_for_request();

private:
    boost::asio::ssl::stream<tcp::socket> m_ssl_socket; // SSL stream
    boost::asio::streambuf m_buffer; // Buffer for reading data
};
