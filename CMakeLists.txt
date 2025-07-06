cmake_minimum_required(VERSION 3.29)
project(PROYECTO2)

set(CMAKE_CXX_STANDARD 20)

add_executable(main
        src/probando.cpp
        src/nn_loss.h
        src/nn_optimizer.h
        src/neural_network.h
        src/nn_activation.h
        src/nn_dense.h
        src/nn_interfaces.h
        src/tensor.h
)
