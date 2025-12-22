/*
 * Copyright (C) 2025 Shreyas Manjunath
 * Client that connects to a TCP server and sends a HEARTBEAT frame.
 */

#include <boost/asio.hpp>
#include <boost/asio/steady_timer.hpp>
#include <iostream>

#include "industrial_tcp/framing.hpp"

using boost::asio::ip::tcp;

void send_heartbeat(tcp::socket& socket, boost::asio::steady_timer& heartbeat_timer)
{
  auto frame = industrial_tcp::framing::make_frame(industrial_tcp::MessageType::HEARTBEAT, {});

  boost::asio::async_write(socket, boost::asio::buffer(frame), [&](const boost::system::error_code& ec, std::size_t) {
    if (ec)
    {
      std::cerr << "[CLIENT] Error sending HEARTBEAT: " << ec.message() << "\n";
      return;
    }

    std::cout << "[CLIENT] Sent HEARTBEAT frame to server\n";

    heartbeat_timer.expires_after(std::chrono::seconds(1));
    heartbeat_timer.async_wait([&](const boost::system::error_code& ec) {
      if (!ec)
      {
        send_heartbeat(socket, heartbeat_timer);
      }
    });
  });
}

void run_client()
{
  try
  {
    boost::asio::io_context io_context;

    tcp::socket socket(io_context);

    boost::asio::steady_timer heartbeat_timer(io_context);

    socket.connect({
        boost::asio::ip::make_address("127.0.0.1"),
        8080,
    });  // Connect to server

    send_heartbeat(socket, heartbeat_timer);
    io_context.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }
}

int main()
{
  run_client();
  return 0;
}
