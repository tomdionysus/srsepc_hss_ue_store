cmake_minimum_required(VERSION 3.14)
project(srsrts-hss-userstore)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(
  /usr/include/mysql
  /usr/local/include/mysql
)

link_directories(
  /usr/lib
  /usr/local/lib
)

add_library(
  srsrts-hss-userstore
  src/user_store_mysql.cpp
)

target_link_libraries(srsrts-hss-userstore mysqlclient)

enable_testing()

add_executable(
  srsrts-hss-userstore_test
  src/user_store_mysql_test.cpp
)

target_link_libraries(
  srsrts-hss-userstore_test
  GTest::gtest_main
  srsrts-hss-userstore
)

add_executable(
  srsrts-hss-userstore-demo
  src/main.cpp
)

target_link_libraries(
  srsrts-hss-userstore-demo
  srsrts-hss-userstore
)

include(GoogleTest)
gtest_discover_tests(srsrts-hss-userstore_test)

include_directories(
  ${CMAKE_BINARY_DIR}/src
  ${CMAKE_BINARY_DIR}/lib
)
