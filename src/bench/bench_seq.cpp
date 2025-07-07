#include <iostream>
#include <chrono>
#include "../../include/utec/nn/dense.h"

using namespace utec::neural_network;
using reloj = std::chrono::high_resolution_clock;

int main() {
    constexpr std::size_t batch = 10'000;
    constexpr std::size_t in_f  = 128;
    constexpr std::size_t out_f = 256;

    Dense<float> capa(in_f,out_f,
        [](auto& W){ W.fill(0.01f); },
        [](auto& b){ b.fill(0.0f); });

    Tensor<float,2> X({batch,in_f});
    for (auto& v : X) v = 0.5f;

    auto t0 = reloj::now();
    auto Y  = capa.forward(X);
    auto t1 = reloj::now();

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
    std::cout << "Secuencial  : " << ms << " ms\n";
    std::cout << "Y(0,0) = " << Y(0,0) << "\n";
}
bench_seq.cpp
