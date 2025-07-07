#include "/include/utec/agent/EnvGym.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;
using namespace utec::neural_network;

EnvGym::EnvGym() {
    srand(static_cast<unsigned>(time(nullptr)));
}

Estado EnvGym::reset() {
    bola_x = 0.5f;
    bola_y = static_cast<float>(rand()) / RAND_MAX;
    vel_x  = -0.02f;
    vel_y  = (rand() % 2 ? 0.015f : -0.015f);
    paleta_y = 0.5f;
    return {bola_x, bola_y, paleta_y};
}

Estado EnvGym::step(int accion, float& recompensa, bool& terminado) {
    paleta_y += paso_paleta * accion;
    if (paleta_y < 0)    paleta_y = 0;
    if (paleta_y > alto) paleta_y = alto;

    bola_x += vel_x;
    bola_y += vel_y;

    if (bola_y < 0) {
        bola_y = 0;
        vel_y  = -vel_y;
    }
    if (bola_y > alto) {
        bola_y = alto;
        vel_y  = -vel_y;
    }

    recompensa = 0.0f;
    terminado  = false;

    if (bola_x - radio_bola <= 0.0f) {
        float distancia = fabs(bola_y - paleta_y);
        if (distancia <= ventana_colision) {
            bola_x = radio_bola;
            vel_x  = -vel_x;
            recompensa = +1.0f;
        } else {
            recompensa = -1.0f;
            terminado  = true;
        }
    }

    if (bola_x + radio_bola >= ancho) {
        bola_x = ancho - radio_bola;
        vel_x  = -vel_x;
    }

    return {bola_x, bola_y, paleta_y};
}
