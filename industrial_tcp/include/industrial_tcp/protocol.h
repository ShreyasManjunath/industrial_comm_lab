/*
 * Copyright (C) 2025 Shreyas Manjunath
 * Industrial TCP Protocol Definitions
 *
 * This file defines the message types and header structure for the Industrial
 * TCP protocol. It ensures proper alignment and packing for network
 * transmission.
 */

#pragma once

#include <cstdint>

namespace industrial_tcp
{
enum class MessageType : uint16_t
{
  HEARTBEAT = 1,
  COMMAND = 2,
  STATUS = 3
};

#pragma pack(push, 1)
struct Header
{
  uint16_t type;    // Message type
  uint32_t length;  // Length of the payload
};
#pragma pack(pop)
}  // namespace industrial_tcp
