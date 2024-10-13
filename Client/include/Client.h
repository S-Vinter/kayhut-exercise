#pragma once

#include <memory>
#include <iostream>
#include <sys/prctl.h>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

using boost::asio::ip::tcp;

static const char NEW_PROGRAM_NAME[] = "innocent";

static const char VERIFY_FILE[] = "/ca.crt";
static const char CERTIFICATE_CHANE_FILE[] = "/client.crt";
static const char PRIVATE_KEY_FILE[] = "/client.key";

class Client
{
public:
    Client(boost::asio::io_context& io_context, boost::asio::ssl::context& ctx, const std::string& host, const std::string& port)
        : m_socket(io_context, ctx) {
        prctl(PR_SET_NAME, (unsigned long) NEW_PROGRAM_NAME);

        ctx.set_options(boost::asio::ssl::context::default_workarounds);
        ctx.load_verify_file(VERIFY_FILE);
        ctx.use_certificate_chain_file(CERTIFICATE_CHANE_FILE);
        ctx.use_private_key_file(PRIVATE_KEY_FILE, boost::asio::ssl::context::pem);

        connect(host, port, io_context);
    }

private:
    void connect(const std::string& host, const std::string& port, boost::asio::io_context& io_context);

    void send_request();

private:
    boost::asio::ssl::stream<tcp::socket> m_socket; // SSL stream
    boost::asio::streambuf m_buffer; // Buffer for reading
};
