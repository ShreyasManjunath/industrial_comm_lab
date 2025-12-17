# 🏭 industrial_comm_lab

**industrial_comm_lab** is a project-based learning repository focused on building **industrial-style networking systems in C++** using **Boost.Asio**, **modern CMake**, and **colcon**.

This repository is not about toy examples. The goal is to **learn networking the way it is used in real industrial, robotics, and control systems** — step by step, by building.

---

## 🎯 Goals

- Learn **asynchronous networking** with Boost.Asio
- Design **binary, framed protocols** (industrial-style)
- Build **robust TCP/UDP communication layers**
- Apply **clean architecture and separation of concerns**
- Prepare a foundation for future topics:
  - Real-time networking
  - DDS / ROS 2
  - Industrial Ethernet (EtherCAT, Profinet concepts)

---

## 🧱 Project Philosophy

This repository follows these principles:

- **Project-based learning** (no isolated snippets)
- **Production-style structure** (headers, sources, layers)
- **Explicit protocols** (no ad-hoc strings)
- **Asynchronous, scalable design**
- **Linux-first**, but portable

Everything added here is something you would realistically see in an industrial or systems-level codebase.

---

## 📦 Current Project: Industrial TCP Control Channel

A robust TCP client/server system with:

- Boost.Asio asynchronous I/O
- Length-prefixed binary protocol
- Session-based server architecture
- Clean separation of:
  - Networking layer
  - Protocol/framing
  - Application logic

This project acts as the **communication backbone** for future extensions.

---

## 🗂️ Repository Structure (Workspace: `industrial_comm_lab`)

```text
industrial_comm_lab/
├── industrial_tcp/        # Boost.Asio TCP communication package
│   ├── CMakeLists.txt
│   ├── package.xml
│   ├── include/industrial_tcp/
│   │   ├── protocol.hpp
│   │   ├── framing.hpp
│   │   └── session.hpp
│   └── src/
│       ├── server.cpp
│       ├── server_main.cpp
│       ├── client.cpp
│       └── client_main.cpp
├── <future_package_1>/    # e.g. UDP, DDS, CAN, etc.
├── <future_package_2>/
└── README.md
```

---

## 🛠️ Build System (Overview)

This repository is organized as a **colcon workspace**.

Each top-level folder (for example `industrial_tcp`) is a **standalone colcon package** with its own:

- `CMakeLists.txt`
- `package.xml`

The workspace is intentionally structured to support **multiple communication projects** (TCP, UDP, DDS, etc.) living side by side.

Detailed build and run instructions will be added **after the core architecture stabilizes**.

### (Build details intentionally omitted for now)

```bash
# Terminal 1
./install/industrial_tcp/lib/industrial_tcp/tcp_server

# Terminal 2
./install/industrial_tcp/lib/industrial_tcp/tcp_client
```

---

## 🧭 Learning Roadmap

Planned milestones for this repository:

1. ✅ Asynchronous TCP server/client (Boost.Asio)
2. ⏳ Heartbeats & watchdog timers
3. ⏳ Command/response protocol
4. ⏳ Multi-threaded `io_context`
5. ⏳ Reconnect & fault handling
6. ⏳ UDP communication path
7. ⏳ Protocol versioning
8. ⏳ Integration patterns (non-RT + RT split)

Later stages may explore:

- Real-time Linux concepts
- DDS-style pub/sub
- Industrial Ethernet concepts

---

## 🧠 Target Audience

- Embedded / systems engineers
- Robotics developers
- Industrial automation engineers
- C++ developers moving into networking

---

## 📜 License

MIT License (intended)

---

## ✍️ Notes

This repository is a **learning lab**, not a finished product.
Expect refactors, experiments, and architectural evolution.

The goal is **understanding**, not shortcuts.
