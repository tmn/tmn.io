cmake_minimum_required(VERSION 3.25)

project(builder)

if(NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  maddy
  URL https://github.com/progsource/maddy/releases/download/1.2.0/maddy-src.zip
)

FetchContent_Declare(
  tinyxml2
  GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
  GIT_TAG master
)

FetchContent_MakeAvailable(maddy tinyxml2)

set(SOURCES
  main.cpp
  tmnio.cpp

  tmnio.h
)

add_executable(builder ${SOURCES})
target_link_libraries(builder PUBLIC maddy tinyxml2)
