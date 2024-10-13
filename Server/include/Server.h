#pragma once

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>
#include <memory>

using boost::asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session>
{
public:
    Session(tcp::socket socket, boost::asio::ssl::context& ctx)
        : m_socket(std::move(socket), ctx) { }

    void run();

private:
    void wait_for_request();

private:
    boost::asio::ssl::stream<tcp::socket> m_socket;
    boost::asio::streambuf m_buffer;
};

class Server
{
public:
    Server(boost::asio::io_context& io_context, short port, boost::asio::ssl::context& ctx)
        : m_acceptor(io_context, tcp::endpoint(tcp::v4(), port)), m_ssl_context(ctx) {
        do_accept();
    }

private:
    void do_accept();

private:
    tcp::acceptor m_acceptor;
    boost::asio::ssl::context& m_ssl_context; // SSL context reference
};
