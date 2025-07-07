#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "../include/utec/nn/neural_network.h"
#include "../include/utec/nn/activation.h"
#include "../include/utec/nn/dense.h"
#include "../include/utec/nn/loss.h"
#include "../include/utec/nn/optimizer.h"

using namespace utec::neural_network;

TEST_CASE("Entrena XOR en < 0.2 loss") {
    using T = float;
    Tensor<T,2> X({4,2});
    X = {0,0 , 0,1 , 1,0 , 1,1};
    Tensor<T,2> Y({4,1});
    Y = {0,1,1,0};

    NeuralNetwork<T> net;
    net.add_layer(std::make_unique<Dense<T>>(2,4,
        [](auto& W){ W.fill(0.5f); },
        [](auto& b){ b.fill(0.0f); }));
    net.add_layer(std::make_unique<ReLU<T>>());
    net.add_layer(std::make_unique<Dense<T>>(4,1,
        [](auto& W){ W.fill(0.5f); },
        [](auto& b){ b.fill(0.0f); }));

    net.train<MSELoss>(X,Y,1000,4,0.1f);

    auto preds = net.predict(X);
    float loss = MSELoss<T,2>(preds,Y).loss();
    REQUIRE(loss < Catch::Approx(0.2f));
}
