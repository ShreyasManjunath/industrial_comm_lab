/*
 * Copyright (C) 2025 Shreyas Manjunath
 * Session class for handling individual TCP connections
 */

#pragma once
#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <cstdint>
#include <iostream>
#include <memory>
#include <utility>
#include <vector>

#include "industrial_tcp/protocol.h"

using boost::asio::ip::tcp;

namespace industrial_tcp
{
class Session : public std::enable_shared_from_this<Session>
{
public:
  explicit Session(tcp::socket socket) : socket_(std::move(socket)), watchdog_(socket_.get_executor())
  {
  }
  void start()
  {
    std::cout << "[SERVER] Session started\n";
    start_watchdog();
    do_read_header();
  }

private:
  void do_read_header()
  {
    auto self(shared_from_this());
    boost::asio::async_read(socket_,
                            boost::asio::buffer(&header_, sizeof(header_)),
                            [this, self](boost::system::error_code ec, std::size_t /*length*/) {
                              if (!ec)
                              {
                                header_.length = ntohl(header_.length);
                                payload_.resize(header_.length);
                                do_read_payload();
                              }
                            });
  }
  void do_read_payload()
  {
    auto self(shared_from_this());
    boost::asio::async_read(
        socket_, boost::asio::buffer(payload_), [this, self](boost::system::error_code ec, std::size_t /*length*/) {
          if (!ec)
          {
            handle_message();
            do_read_header();
          }
        });
  }
  void handle_message()
  {
    // Process the message based on its type
    std::cout << "Received message of type: " << ntohs(header_.type) << ", length: " << ntohl(header_.length)
              << std::endl;
    if (ntohs(header_.type) == std::to_underlying(MessageType::HEARTBEAT))  // to_underlying requires C++23
    {
      std::cout << "[SERVER] Watchdog reset\n";
      watchdog_.expires_after(timeout_);
    }
  }

  void start_watchdog()
  {
    std::cout << "[SERVER] Watchdog started\n";
    watchdog_.expires_after(timeout_);
    watchdog_.async_wait([self = shared_from_this()](const boost::system::error_code& ec) {
      if (ec == boost::asio::error::operation_aborted)
      {
        // Timer was reset — re-arm it
        self->start_watchdog();
        return;
      }
      if (!ec)
      {
        std::cout << "[SERVER] Connection timed out due to inactivity. Timemout is set to 5s.\n";
        std::cout << "[SERVER] Watchdog expired\n";
        boost::asio::post(self->socket_.get_executor(), [self]() {
          self->socket_.cancel();
          self->socket_.close();
        });
      }
      else
      {
        std::cout << "[SERVER] Watchdog cancelled/reset\n";
      }
    });
  }

  // Member variables
  tcp::socket socket_;
  Header header_;
  std::vector<uint8_t> payload_;
  boost::asio::steady_timer watchdog_;
  std::chrono::seconds timeout_{ 5 };
};
}  // namespace industrial_tcp
