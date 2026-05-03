cmake_minimum_required(VERSION 3.17)

project(secureFS)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(include)

add_executable(secureFS src/secureFileSystem.cpp src/main.cpp src/userAccessHandler.cpp src/authorizationHandler.cpp src/credentialStore.cpp)