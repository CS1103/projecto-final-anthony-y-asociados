#ifndef UTEC_AGENT_ENVGYM_H
#define UTEC_AGENT_ENVGYM_H

#include "PongAgent.h"

namespace utec::neural_network {

class EnvGym {
private:
    /* constantes normalizadas */
    static constexpr float ancho            = 1.0f;
    static constexpr float alto             = 1.0f;
    static constexpr float paso_paleta      = 0.05f;
    static constexpr float radio_bola       = 0.03f;
    static constexpr float ventana_colision = 0.10f;

    float bola_x{}, bola_y{};
    float vel_x{}, vel_y{};
    float paleta_y{};

public:
    EnvGym();
    Estado reset();
    Estado step(int accion, float& recompensa, bool& fin);
};

} // namespace utec::neural_network
#endif
