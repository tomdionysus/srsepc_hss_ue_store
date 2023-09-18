cmake_minimum_required(VERSION 3.14)
project(srsepc_hss_ue_store)

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

find_package(PostgreSQL REQUIRED)

include_directories(
  /usr/include/mysql
  /usr/local/include/mysql
  ${PostgreSQL_INCLUDE_DIRS}
  ./
)

link_directories(
  /usr/lib
  /usr/local/lib
)

add_library(
  srsepc_hss_ue_store
  src/ue_store_csv.cc
  src/ue_store_mysql.cc
  src/ue_store_psql.cc
)

target_link_libraries(
  srsepc_hss_ue_store 
  mysqlclient
  PostgreSQL::PostgreSQL
)

enable_testing()

add_executable(
  srsepc_hss_ue_store_test
  src/ue_store_mysql_test.cc
  src/ue_store_psql_test.cc
)

target_link_libraries(
  srsepc_hss_ue_store_test
  GTest::gtest_main
  srsepc_hss_ue_store
)

include(GoogleTest)
gtest_discover_tests(srsepc_hss_ue_store_test)

include_directories(
  ${CMAKE_BINARY_DIR}/src
  ${CMAKE_BINARY_DIR}/lib
)
