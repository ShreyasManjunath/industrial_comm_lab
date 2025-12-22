cmake_minimum_required(VERSION 3.16)
project(industrial_tcp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find ROS2 and Boost
find_package(ament_cmake REQUIRED)
# find_package(rclcpp REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)

# Include directories
include_directories(
  include
  ${Boost_INCLUDE_DIRS}
)

# Server executable
add_executable(tcp_server src/server.cpp)
target_include_directories(tcp_server PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(tcp_server
  Boost::system
  pthread
)

# Client executable
add_executable(tcp_client src/client.cpp)
target_include_directories(tcp_client PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
target_link_libraries(tcp_client
  Boost::system
  pthread
)

# Install targets
install(TARGETS tcp_server tcp_client
  RUNTIME DESTINATION lib/${PROJECT_NAME}
)

# Install headers
install(DIRECTORY include/
  DESTINATION include/${PROJECT_NAME}
)

# Export package
ament_package()
