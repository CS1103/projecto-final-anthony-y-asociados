cmake_minimum_required(VERSION 3.29)
project(PROYECTO2)

set(CMAKE_CXX_STANDARD 20)

add_executable(main
        probando.cpp
        nn_loss.h
        nn_optimizer.h
        neural_network.h
        nn_activation.h
        nn_dense.h
        nn_interfaces.h
        tensor.h
)
