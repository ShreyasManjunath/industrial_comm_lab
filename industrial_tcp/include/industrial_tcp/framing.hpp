/*
 * Copyright 2025 Shreyas Manjunath
 * Framing utilities for industrial_tcp protocol
 */

#pragma once
#include <cstring>
#include <vector>

#include "industrial_tcp/protocol.h"

namespace industrial_tcp::framing
{
inline std::vector<uint8_t> make_frame(MessageType type, const std::vector<uint8_t>& payload)
{
  Header header;
  header.type = static_cast<uint16_t>(type);
  header.length = static_cast<uint32_t>(payload.size());

  std::vector<uint8_t> frame(sizeof(header) + payload.size());
  std::memcpy(frame.data(), &header, sizeof(header));
  std::memcpy(frame.data() + sizeof(header), payload.data(), payload.size());

  return frame;
}
}  // namespace industrial_tcp::framing
