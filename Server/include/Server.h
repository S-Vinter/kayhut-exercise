#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "Session.h"

using boost::asio::ip::tcp;

static const char VERIFY_FILE[] = "/ca.crt";
static const char CERTIFICATE_CHANE_FILE[] = "/server.crt";
static const char PRIVATE_KEY_FILE[] = "/server.key";

class Server {
public:
    // Constructor initializes the acceptor and SSL context
    Server(boost::asio::io_context& io_context, short port, boost::asio::ssl::context& ctx)
        : m_acceptor(io_context, tcp::endpoint(tcp::v4(), port)), m_ssl_context(ctx) {
        // Load server's certificate and private key
        ctx.set_options(boost::asio::ssl::context::default_workarounds | boost::asio::ssl::context::no_sslv2);
        ctx.use_certificate_chain_file(CERTIFICATE_CHANE_FILE);
        ctx.use_private_key_file(PRIVATE_KEY_FILE, boost::asio::ssl::context::pem);
        ctx.load_verify_file(VERIFY_FILE);

        do_accept();
    }

private:
    // Accept new connections
    void do_accept();

private:
    tcp::acceptor m_acceptor; // TCP acceptor for incoming connections
    boost::asio::ssl::context& m_ssl_context; // SSL context
};
