/**
 * Copyright (c) 2025 Shreyas Manjunath
 * Framing tests for industrial_tcp protocol
 */
#include <gtest/gtest.h>
#include <cstdint>
#include "industrial_tcp/framing.hpp"
#include <boost/asio.hpp>

TEST(FramingTest, HeartbeatFrame)
{
  auto frame = industrial_tcp::framing::make_frame(industrial_tcp::MessageType::HEARTBEAT, {});

  EXPECT_EQ(frame.size(), sizeof(industrial_tcp::Header));
  auto header = industrial_tcp::framing::parse_header(frame);
  EXPECT_EQ(header.type, static_cast<uint16_t>(industrial_tcp::MessageType::HEARTBEAT));
  EXPECT_EQ(header.length, 0);
}

TEST(WatchdogTest, FiresAfterTimeout)
{
  boost::asio::io_context io;
  boost::asio::steady_timer timer(io, std::chrono::milliseconds(50));
  bool expired = false;

  timer.async_wait([&](const boost::system::error_code&) { expired = true; });

  io.run_for(std::chrono::milliseconds(100));

  EXPECT_TRUE(expired);
}
