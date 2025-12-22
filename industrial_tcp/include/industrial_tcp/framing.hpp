/*
 * Copyright 2025 Shreyas Manjunath
 * Framing utilities for industrial_tcp protocol
 */

#pragma once
#include <cstring>
#include <vector>
#include <stdexcept>
#include <cstdint>
#include <arpa/inet.h>

#include "industrial_tcp/protocol.h"

namespace industrial_tcp::framing
{
inline std::vector<uint8_t> make_frame(MessageType type, const std::vector<uint8_t>& payload)
{
  Header header;
  // tcp protocols use network byte order (big-endian)
  header.type = htons(static_cast<uint16_t>(type));
  header.length = htonl(static_cast<uint32_t>(payload.size()));

  std::vector<uint8_t> frame(sizeof(header) + payload.size());
  std::memcpy(frame.data(), &header, sizeof(header));
  std::memcpy(frame.data() + sizeof(header), payload.data(), payload.size());

  return frame;
}
inline Header parse_header(const std::vector<uint8_t>& frame)
{
  Header header;
  if (frame.size() < sizeof(header))
  {
    throw std::runtime_error("Frame too small to contain header");
  }
  std::memcpy(&header, frame.data(), sizeof(header));
  header.type = ntohs(header.type);
  header.length = ntohl(header.length);
  return header;
}
}  // namespace industrial_tcp::framing
