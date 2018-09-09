project(speaker C)
cmake_minimum_required(VERSION 3.9)

# Create the speaker library
add_library(speaker SHARED
  ${CMAKE_CURRENT_SOURCE_DIR}/say.c
  ${CMAKE_CURRENT_SOURCE_DIR}/shout.c
)
target_include_directories(speaker
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Create a headers only speaker library
add_library(speaker-headers INTERFACE)
target_include_directories(speaker-headers
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Do the install stuff
