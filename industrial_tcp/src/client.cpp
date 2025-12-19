/*
 * Copyright (C) 2025 Shreyas Manjunath
 * Client that connects to a TCP server and sends a HEARTBEAT frame.
 */

#include <boost/asio.hpp>
#include <iostream>

#include "industrial_tcp/framing.hpp"

using boost::asio::ip::tcp;

void run_client()
{
  try
  {
    boost::asio::io_context io_context;

    tcp::socket socket(io_context);

    socket.connect({
        boost::asio::ip::make_address("127.0.0.1"),
        8080,
    });  // Connect to server

    auto frame =
        industrial_tcp::framing::make_frame(industrial_tcp::MessageType::HEARTBEAT, {});  // Empty payload for heartbeat
    boost::asio::write(socket, boost::asio::buffer(frame));
    std::cout << "Sent HEARTBEAT frame to server\n";
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
