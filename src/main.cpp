#include <iostream>
#include "../include/utec/nn/neural_network.h"
#include "../include/utec/nn/dense.h"
#include "../include/utec/nn/activation.h"
#include "../include/utec/nn/loss.h"
#include "../include/utec/agent/PongAgent.h"
#include "../include/utec/agent/EnvGym.h"

using namespace std;
using namespace utec::neural_network;

int main() {
    using T = float;
    Tensor<T,2> X({4,2});
    X = {0,0, 0,1, 1,0, 1,1};
    Tensor<T,2> Y({4,1});
    Y = {0,1,1,0};

    NeuralNetwork<T> net;
    net.add_layer(make_unique<Dense<T>>(2,4,
        [](auto& W){ W.fill(0.5f); },
        [](auto& b){ b.fill(0.0f); }));
    net.add_layer(make_unique<ReLU<T>>());
    net.add_layer(make_unique<Dense<T>>(4,1,
        [](auto& W){ W.fill(0.5f); },
        [](auto& b){ b.fill(0.0f); }));

    net.train<MSELoss>(X,Y, /*epochs*/500, /*batch*/4, /*lr*/0.1f);
    cout << "Entrenamiento XOR finalizado.\n";

    auto modelo = make_unique<Dense<T>>(3,1,
        [](auto& W){ // peso solo en bola_y
            W.fill(0.0f); W(1,0) = 10.0f;
        },
        [](auto& b){ b.fill(-5.0f); });

    PongAgent<T> agente(move(modelo));
    cout << "PongAgent creado.\n";

    EnvGym env;
    auto estado = env.reset();
    float recompensa; bool fin;

    for (int paso=0; paso<10 && !fin; ++paso) {
        int acc = agente.actuar(estado);
        estado  = env.step(acc, recompensa, fin);
        cout << "Paso " << paso
             << " | acción=" << acc
             << " | recompensa=" << recompensa
             << " | fin=" << fin << "\n";
    }
    return 0;
}
