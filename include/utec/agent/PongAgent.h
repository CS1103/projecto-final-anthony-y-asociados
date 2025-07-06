/*===============================================================
  PongAgent.h
  ---------------------------------------------------------------
  Agente que decide cómo mover la paleta en un Pong simplificado
  usando la red neuronal que ya implementaste.
  Acción devuelta:
        -1  → subir la paleta
         0  → quedarse quieto
        +1  → bajar la paleta
===============================================================*/
#ifndef UTEC_AGENT_PONGAGENT_H
#define UTEC_AGENT_PONGAGENT_H

#include "../nn/nn_interfaces.h"    // ILayer y Tensor
#include <memory>                   // std::unique_ptr

using namespace std;                // preferencia del usuario
using utec::algebra::Tensor;        // alias al Tensor

namespace utec::neural_network {    // ← mismo namespace de tu núcleo

/*---------------------------------------------------------------
  Estado del juego (3 datos mínimos normalizados 0-1)
---------------------------------------------------------------*/
struct Estado {
    float bola_x;     // posición horizontal de la bola
    float bola_y;     // posición vertical de la bola
    float paleta_y;   // centro vertical de la paleta
};

/*---------------------------------------------------------------
  Clase plantilla PongAgent
---------------------------------------------------------------*/
template <typename T>
class PongAgent {
private:
    unique_ptr<ILayer<T>> modelo;   // red neuronal que decide

public:
    /*-----------------------------------------------------------
      Constructor: recibe la red neuronal ya creada/entrenada
    -----------------------------------------------------------*/
    PongAgent(unique_ptr<ILayer<T>> modelo_recibido) {
        modelo = move(modelo_recibido);   // sin lista de inicialización
    }

    /*-----------------------------------------------------------
      Método actuar: devuelve -1, 0 o +1 según la predicción
    -----------------------------------------------------------*/
    int actuar(const Estado& e) {
        /* 1. Preparo la entrada para la red (batch 1 × 3) */
        Tensor<T,2> entrada({1,3});
        entrada(0,0) = e.bola_x;
        entrada(0,1) = e.bola_y;
        entrada(0,2) = e.paleta_y;

        /* 2. Propago hacia adelante */
        Tensor<T,2> salida = modelo->forward(entrada);
        T y = salida(0,0);                // asumo 1 neurona de salida

        /* 3. Interpreto la salida como orden de movimiento */
        if (y >  0.1) return  1;          // bajar paleta
        if (y < -0.1) return -1;          // subir paleta
        return 0;                         // quedarse quieto
    }
};

} // namespace utec::neural_network
#endif /* UTEC_AGENT_PONGAGENT_H */
