cmake_minimum_required(VERSION 3.18)
project(PongAI LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(include)

file(GLOB_RECURSE ALL_SRC "src/*.cpp")

set(MAIN_SRC     src/main.cpp)
set(BENCH_SEQ_SRC    src/bench/bench_seq.cpp)
set(BENCH_THREAD_SRC src/bench/bench_thread.cpp)

list(REMOVE_ITEM ALL_SRC ${MAIN_SRC} ${BENCH_SEQ_SRC} ${BENCH_THREAD_SRC})

add_library(ponglib STATIC ${ALL_SRC})

# pthread (solo Linux / WSL / MinGW)
if (UNIX AND NOT APPLE)
    target_link_libraries(ponglib PUBLIC pthread)
elseif (MINGW)
    target_link_libraries(ponglib PUBLIC pthread)
endif()

add_executable(pong_demo ${MAIN_SRC})
target_link_libraries(pong_demo PRIVATE ponglib)

add_executable(bench_seq    ${BENCH_SEQ_SRC})
add_executable(bench_thread ${BENCH_THREAD_SRC})

target_link_libraries(bench_seq    PRIVATE ponglib)
target_link_libraries(bench_thread PRIVATE ponglib)

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
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain ponglib)

add_test(NAME all_tests COMMAND tests)
