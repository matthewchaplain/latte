project(LogAllTheThings)
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)

add_library(logallthethings)
target_sources(logallthethings PRIVATE src/dummy.cc)
target_include_directories(logallthethings PUBLIC include)

add_executable(journal_log)
target_sources(journal_log PRIVATE journal_log/main.cc)
target_link_libraries(journal_log PUBLIC logallthethings)