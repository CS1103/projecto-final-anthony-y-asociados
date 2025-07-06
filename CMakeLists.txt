cmake_minimum_required(VERSION 3.29)
project(PROYECTO2)

set(CMAKE_CXX_STANDARD 20)

add_executable(main
        tests/test_tensor.cpp
        tests/test_neural_network.cpp
        tests/test_agent_env.cpp
        src/utec/agent/PongAgent.cpp
        src/utec/agent/EnvGym.cpp
        include/utec/algebra/tensor.h
        include/utec/nn/layer.h
        include/utec/nn/dense.h
        include/utec/nn/activation.h
        include/utec/nn/loss.h
        include/utec/nn/neural_network.h
        include/utec/nn/optimization.h
        include/utec/agent/PongAgent.h
        include/utec/agent/EnvGym.h        
)
