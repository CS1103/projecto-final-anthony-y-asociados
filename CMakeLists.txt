cmake_minimum_required(VERSION 3.18)
project(PongAI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

file(GLOB_RECURSE ALL_SRC   "src/*.cpp")

file(GLOB_RECURSE BENCH_SRC "src/bench/*.cpp")

set(CORE_SRC ${ALL_SRC})
list(REMOVE_ITEM CORE_SRC ${BENCH_SRC})

add_executable(pong_demo ${CORE_SRC})

if (UNIX AND NOT APPLE)
    target_link_libraries(pong_demo pthread)
elseif (MINGW)
    target_link_libraries(pong_demo pthread)
endif()

add_executable(bench_seq    src/bench/bench_seq.cpp)
add_executable(bench_thread src/bench/bench_thread.cpp)

if (UNIX AND NOT APPLE)
    target_link_libraries(bench_seq    pthread)
    target_link_libraries(bench_thread pthread)
elseif (MINGW)
    target_link_libraries(bench_seq    pthread)
    target_link_libraries(bench_thread pthread)
endif()

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

file(GLOB_RECURSE TEST_SRC "tests/*.cpp")
add_executable(tests ${TEST_SRC})
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_test(NAME all_tests COMMAND tests)
