#ifndef UTEC_AGENT_ENVGYM_H
#define UTEC_AGENT_ENVGYM_H

#include "PongAgent.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

namespace utec::neural_network {

class EnvGym {
private:
    const float ancho  = 1.0f;
    const float alto   = 1.0f;
    const float paso_paleta = 0.05f;
    const float radio_bola  = 0.03f;

    float bola_x;
    float bola_y;
    float vel_x;
    float vel_y;
    float paleta_y;

public:
    EnvGym() {
        srand(static_cast<unsigned>(time(nullptr)));
    }

    Estado reset() {
        bola_x = 0.5f;
        bola_y = static_cast<float>(rand())/RAND_MAX;
        vel_x  = -0.02f;
        vel_y  = (rand()%2 ? 0.015f : -0.015f);
        paleta_y = 0.5f;
        return {bola_x, bola_y, paleta_y};
    }

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
                bola_x = radio_bola;
                vel_x  = -vel_x;
                recompensa = +1;
            } else {
                recompensa = -1;
                terminado  = true;
            }
        }

        if (bola_x + radio_bola >= ancho) {
            bola_x = ancho - radio_bola;
            vel_x  = -vel_x;
        }

        return {bola_x, bola_y, paleta_y};
    }
};

} // namespace utec::neural_network
#endif /* UTEC_AGENT_ENVGYM_H */
