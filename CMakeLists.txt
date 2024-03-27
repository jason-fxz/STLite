cmake_minimum_required(VERSION 3.0.0)
project(code VERSION 0.1.0 LANGUAGES C CXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CPPFLAGS} -g -O0")
set(CMAKE_CXX_STANDARD 20)
# set(ENV{LSAN_OPTIONS} "verbosity=1:log_threads=1")

# include(CTest)
# enable_testing()

add_executable(code map/src/task2.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
