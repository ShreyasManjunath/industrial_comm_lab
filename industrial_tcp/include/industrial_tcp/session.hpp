/*
 * Copyright (C) 2025 Shreyas Manjunath
 * Session class for handling individual TCP connections
 */

#pragma once
#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "industrial_tcp/protocol.h"

using boost::asio::ip::tcp;

namespace industrial_tcp {
class Session : public std::enable_shared_from_this<Session> {
 public:
  explicit Session(tcp::socket socket) : socket_(std::move(socket)) {}
  void start() { do_read_header(); }

 private:
  void do_read_header() {
    auto self(shared_from_this());
    boost::asio::async_read(
        socket_, boost::asio::buffer(&header_, sizeof(header_)),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
          if (!ec) {
            header_.length = ntohl(header_.length);
            payload_.resize(header_.length);
            do_read_payload();
          }
        });
  }
  void do_read_payload() {
    auto self(shared_from_this());
    boost::asio::async_read(
        socket_, boost::asio::buffer(payload_),
        [this, self](boost::system::error_code ec, std::size_t /*length*/) {
          if (!ec) {
            handle_message();
            do_read_header();
          }
        });
  }
  void handle_message() {
    // Process the message based on its type
    std::cout << "Received message of type: " << header_.type
              << ", length: " << header_.length << std::endl;
  }

  // Member variables
  tcp::socket socket_;
  Header header_;
  std::vector<uint8_t> payload_;
};
}  // namespace industrial_tcp
