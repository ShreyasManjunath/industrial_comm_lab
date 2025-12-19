/*
 * Copyright (C) 2025 Shreyas Manjunath
 * TCP Server using Boost.Asio and industrial_tcp library
 * Listens for incoming connections and starts a session for each client
 */

#include <boost/asio.hpp>
#include <iostream>
#include <memory>

#include "industrial_tcp/session.hpp"

using boost::asio::ip::tcp;

class Server {
 public:
  Server(boost::asio::io_context& io_context, unsigned short port)
      : acceptor_(io_context, tcp::endpoint(tcp::v4(), port)) {
    do_accept();
  }

 private:
  void do_accept() {
    acceptor_.async_accept([this](boost::system::error_code ec,
                                  tcp::socket socket) {
      if (!ec) {
        std::make_shared<industrial_tcp::Session>(std::move(socket))->start();
      }
      do_accept();
    });
  }

  tcp::acceptor acceptor_;
};

int main(int argc, char* argv[]) {
  try {
    // the input argument is the port number
    if (argc != 2) {
      std::cerr << "Usage: tcp_server <port>\n";
      return 1;
    }

    auto port = std::atoi(argv[1]);
    boost::asio::io_context io_context;
    Server server(io_context, port);
    std::cout << "Server running on port " << port << std::endl;
    io_context.run();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
