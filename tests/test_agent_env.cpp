#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "../include/utec/agent/PongAgent.h"
#include "../include/utec/agent/EnvGym.h"
#include "../include/utec/nn/dense.h"

using namespace utec::neural_network;

TEST_CASE("PongAgent actúa coherentemente") {
    auto capa = std::make_unique<Dense<float>>(3,1,
        [](auto& W){ W.fill(0.0f); W(1,0)=10.0f; },
        [](auto& b){ b.fill(-5.0f); });

    PongAgent<float> agente(std::move(capa));

    SECTION("bola arriba") {
        Estado e{0.5f,0.9f,0.3f};
        REQUIRE(agente.actuar(e) == 1);
    }
    SECTION("bola abajo") {
        Estado e{0.5f,0.1f,0.7f};
        REQUIRE(agente.actuar(e) == -1);
    }
}

TEST_CASE("EnvGym rebota y termina") {
    EnvGym env;
    float r; bool fin;
    auto s = env.reset();
    for(int t=0;t<500 && !fin;++t) s = env.step(0,r,fin);
    REQUIRE(fin);
    REQUIRE((r==1.0f || r==-1.0f));
}
