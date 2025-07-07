#ifndef UTEC_AGENT_PONGAGENT_H
#define UTEC_AGENT_PONGAGENT_H

#include "../nn/layer.h"
#include <memory>

using namespace std;
using utec::algebra::Tensor;

namespace utec::neural_network {

struct Estado {
    float bola_x;
    float bola_y;
    float paleta_y;
};

template <typename T>
class PongAgent {
private:
    unique_ptr<ILayer<T>> modelo;

public:
    PongAgent(unique_ptr<ILayer<T>> modelo_recibido) {
        modelo = move(modelo_recibido);
    }

    int actuar(const Estado& e) {
        Tensor<T,2> entrada({1,3});
        entrada(0,0) = e.bola_x;
        entrada(0,1) = e.bola_y;
        entrada(0,2) = e.paleta_y;

        Tensor<T,2> salida = modelo->forward(entrada);
        T y = salida(0,0);

        if (y >  0.1) return  1;
        if (y < -0.1) return -1;
        return 0;
    }
};

} // namespace utec::neural_network
#endif /* UTEC_AGENT_PONGAGENT_H */
