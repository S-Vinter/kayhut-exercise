#pragma once

#include <memory>
#include <iostream>
#include <sys/prctl.h>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;

static const char NEW_PROGRAM_NAME[] = "innocent";

class Client
{
public:
    Client(boost::asio::io_context& io_context, boost::asio::ssl::context& ctx, const std::string& host, const std::string& port)
        : m_socket(io_context, ctx) {
        prctl(PR_SET_NAME, (unsigned long) NEW_PROGRAM_NAME);
        connect(host, port, io_context);
    }

private:
    void connect(const std::string& host, const std::string& port, boost::asio::io_context& io_context);

    void send_request();

    void read_response();

private:
    boost::asio::ssl::stream<tcp::socket> m_socket; // SSL stream
    boost::asio::streambuf m_buffer; // Buffer for reading
};
