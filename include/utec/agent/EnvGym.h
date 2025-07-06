/*===============================================================
  EnvGym.h
  ---------------------------------------------------------------
  Entorno minimalista tipo “Gym” para el Pong simplificado.
  - reset()  → reinicia el juego y devuelve Estado inicial.
  - step(a, r, terminado) →
        * aplica la acción del agente  (-1,0,+1)
        * actualiza física simple de bola
        * devuelve el nuevo Estado y la recompensa:
              +1  bola rebotada con éxito
              -1  bola se fue sin ser alcanzada
===============================================================*/
#ifndef UTEC_AGENT_ENVGYM_H
#define UTEC_AGENT_ENVGYM_H

#include "PongAgent.h"      // usa la misma estructura Estado
#include <cstdlib>          // rand()
#include <ctime>

using namespace std;        // preferencia del usuario

namespace utec::neural_network {

class EnvGym {
private:
    /* --- parámetros fijos del juego --- */
    const float ancho  = 1.0f;
    const float alto   = 1.0f;
    const float paso_paleta = 0.05f;
    const float radio_bola  = 0.03f;

    /* --- estado interno --- */
    float bola_x;
    float bola_y;
    float vel_x;
    float vel_y;
    float paleta_y;

public:
    /*--------------- constructor -----------------------------*/
    EnvGym() {
        srand(static_cast<unsigned>(time(nullptr)));
        /* cuerpo vacío: todo se inicializa en reset() */
    }

    /*--------------- reinicia el episodio --------------------*/
    Estado reset() {
        bola_x = 0.5f;
        bola_y = static_cast<float>(rand())/RAND_MAX;   // aleatorio
        vel_x  = -0.02f;                                // va a la izquierda
        vel_y  = (rand()%2 ? 0.015f : -0.015f);         // arriba o abajo
        paleta_y = 0.5f;
        return {bola_x, bola_y, paleta_y};
    }

    /*--------------- avanza un paso --------------------------*/
    Estado step(int accion, float& recompensa, bool& terminado) {
        /* 1. mover paleta según acción (-1,0,+1) */
        paleta_y += paso_paleta * accion;
        if (paleta_y < 0) paleta_y = 0;
        if (paleta_y > alto) paleta_y = alto;

        /* 2. mover bola */
        bola_x += vel_x;
        bola_y += vel_y;

        /* rebote en techo / piso */
        if (bola_y < 0) { bola_y = 0; vel_y = -vel_y; }
        if (bola_y > alto) { bola_y = alto; vel_y = -vel_y; }

        recompensa = 0;
        terminado  = false;

        /* 3. colisión con paleta (x≈0) */
        if (bola_x - radio_bola <= 0.0f) {
            float distancia = fabs(bola_y - paleta_y);
            if (distancia <= 0.1f) {
                /* éxito: rebota hacia la derecha */
                bola_x = radio_bola;
                vel_x  = -vel_x;
                recompensa = +1;
            } else {
                /* falla: fin de episodio */
                recompensa = -1;
                terminado  = true;
            }
        }

        /* 4. colisión borde derecho: rebota automáticamente */
        if (bola_x + radio_bola >= ancho) {
            bola_x = ancho - radio_bola;
            vel_x  = -vel_x;
        }

        return {bola_x, bola_y, paleta_y};
    }
};

} // namespace utec::neural_network
#endif /* UTEC_AGENT_ENVGYM_H */