project(basic C)
cmake_minimum_required(VERSION 3.9)

if("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")
  message(SEND_ERROR "In-source builds are not allowed.")
endif("${PROJECT_SOURCE_DIR}" STREQUAL "${PROJECT_BINARY_DIR}")

add_subdirectory(speaker)

add_executable(speak
  ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)
target_link_libraries(speak
  PRIVATE
    speaker
    speaker-headers
)
