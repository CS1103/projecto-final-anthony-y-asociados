cmake_minimum_required(VERSION 3.29)
project(AnthonyYAsociados)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

file(GLOB_RECURSE SRC "src/*.cpp")
add_executable(pong ${SRC})

if (UNIX AND NOT APPLE)
    target_link_libraries(pong pthread)
elseif (MINGW)
    target_link_libraries(pong pthread)
endif()

add_executable(bench_seq    src/bench/bench_seq.cpp)
add_executable(bench_thread src/bench/bench_thread.cpp)

if (UNIX AND NOT APPLE)
    target_link_libraries(bench_thread pthread)
    target_link_libraries(bench_seq   pthread)
elseif (MINGW)
    target_link_libraries(bench_thread pthread)
    target_link_libraries(bench_seq   pthread)
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
