#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>
#include <memory>

using boost::asio::ip::tcp;

static const char VERIFY_FILE[] = "/ca.crt";
static const char CERTIFICATE_CHANE_FILE[] = "/server.crt";
static const char PRIVATE_KEY_FILE[] = "/server.key";

class Session : public std::enable_shared_from_this<Session> {
public:
    // Constructor takes a socket and an SSL context
    Session(tcp::socket socket, boost::asio::ssl::context& ctx)
        : m_ssl_socket(std::move(socket), ctx) {
            // Load server's certificate and private key
            ctx.set_options(boost::asio::ssl::context::default_workarounds | boost::asio::ssl::context::no_sslv2);
            ctx.use_certificate_chain_file(CERTIFICATE_CHANE_FILE);
            ctx.use_private_key_file(PRIVATE_KEY_FILE, boost::asio::ssl::context::pem);
            ctx.load_verify_file(VERIFY_FILE);
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

class Server {
public:
    // Constructor initializes the acceptor and SSL context
    Server(boost::asio::io_context& io_context, short port, boost::asio::ssl::context& ctx)
        : m_acceptor(io_context, tcp::endpoint(tcp::v4(), port)), m_ssl_context(ctx) {
        do_accept();
    }

private:
    // Accept new connections
    void do_accept();

private:
    tcp::acceptor m_acceptor; // TCP acceptor for incoming connections
    boost::asio::ssl::context& m_ssl_context; // SSL context
};
