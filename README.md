# 🏭 industrial_comm_lab

**industrial_comm_lab** is a project-based learning repository focused on building **industrial-style networking systems in C++** using **Boost.Asio**, **modern CMake**, **colcon**, and **ROS2**.

This repository is not about toy examples. The goal is to **learn networking the way it is used in real industrial, robotics, and control systems** — step by step, by building.

---

## 🎯 Goals

- Learn **asynchronous networking** with Boost.Asio in ROS2
- Design **binary, framed protocols** (industrial-style)
- Build **robust TCP/UDP communication layers**
- Apply **clean architecture and separation of concerns**
- Prepare a foundation for future topics:
  - Heartbeats and watchdog timers
  - Multi-threaded I/O contexts
  - Real-time networking
  - DDS / ROS 2 integration
  - Industrial Ethernet (EtherCAT, Profinet concepts)

---

## 🧱 Project Philosophy

This repository follows these principles:

- **Project-based learning** (no isolated snippets)
- **Production-style structure** (headers, sources, layers)
- **Explicit protocols** (no ad-hoc strings)
- **Asynchronous, scalable design**
- **Linux-first**, ROS2-ready, but portable

Everything added here is something you would realistically see in an industrial or systems-level codebase.

---

## 📦 Repository Structure (Workspace: `industrial_comm_lab`)

```text
industrial_comm_lab/
├── industrial_tcp/        # ROS2 Boost.Asio TCP communication package
│   ├── CMakeLists.txt
│   ├── package.xml
│   ├── include/industrial_tcp/
│   │   ├── protocol.hpp
│   │   ├── framing.hpp
│   │   └── session.hpp
│   └── src/
│       ├── server.cpp
│       └── client.cpp
├── <future_package_1>/    # e.g. UDP, DDS, CAN, etc.
├── <future_package_2>/
└── README.md
```

---

## 🛠️ Build System (Overview)

This repository is organized as a **colcon workspace**.

Each top-level folder (for example `industrial_tcp`) is a **standalone ROS2 colcon package** with its own:

- `CMakeLists.txt`
- `package.xml`

The workspace is intentionally structured to support **multiple communication projects** (TCP, UDP, DDS, etc.) living side by side.

Detailed build and run instructions will be added **after the core architecture stabilizes**.

### (Build details intentionally omitted for now)

---

## 🧭 Learning Roadmap

**Milestone 1 (Complete):**

- ROS2 industrial_tcp package
- Asynchronous TCP server and client
- Basic connection works
- Headers & include structure set up

**Milestone 2 (Complete): Heartbeats & Watchdog Timers**

- Client sends periodic HEARTBEAT frames to the server
- Server monitors each session with a watchdog timer
- Watchdog resets on heartbeat receipt and expires after inactivity
- Safe asynchronous socket closure on timeout (no crashes)
- Unit tests for framing, heartbeat, and network byte order validation
- Verified robustness with Boost.Asio async timers

**Next Milestones:**
3. Command/response protocol with robust framing (handling partial TCP reads)
4. Multi-threaded `io_context`
5. Reconnect & fault handling
6. UDP communication path
7. Protocol versioning
8. Integration patterns (non-RT + RT split)

Later stages may explore:

- Real-time Linux concepts
- DDS-style pub/sub
- Industrial Ethernet concepts

---

## 🧠 Target Audience

- Embedded / systems engineers
- Robotics developers
- Industrial automation engineers
- C++ developers moving into networking and ROS2

---

## 📜 License

This repository is released under the MIT License. You are free to use, modify, and distribute the code for personal, educational, or commercial purposes, with proper attribution.

---

## ✍️ Notes

This repository is a **learning lab**, not a finished product.
Expect refactors, experiments, and architectural evolution.

The goal is **understanding**, not shortcuts.
