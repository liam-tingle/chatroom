cmake_minimum_required(VERSION 3.11.4)
project(Chatroom)
set(ENABLE_NETLIB  ON  CACHE BOOL "Adds Networking to the Project" FORCE)
include(CMake/netlib.cmake)
add_subdirectory(Client)
add_subdirectory(Server)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0" )