#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "../include/utec/algebra/Tensor.h"

using utec::algebra::Tensor;

TEST_CASE("Tensor reshape válido") {
    Tensor<int,2> t({2,3});
    t.fill(1);
    t.reshape(3,2);
    REQUIRE(t.shape()[0] == 3);
    REQUIRE(t.shape()[1] == 2);
}

TEST_CASE("Broadcast + operador *") {
    Tensor<int,2> a({2,1});
    a(0,0)=2; a(1,0)=3;
    Tensor<int,2> b({2,3});
    b.fill(4);
    auto c = a * b;
    REQUIRE(c(0,2) == 8);
    REQUIRE(c(1,1) == 12);
}

TEST_CASE("matrix_product 2×2") {
    Tensor<float,2> A({2,2});
    Tensor<float,2> B({2,2});
    A = {1,2,3,4};      // row-major
    B = {5,6,7,8};
    auto C = utec::algebra::matrix_product(A,B);
    REQUIRE(C(0,0) == Approx(19));
    REQUIRE(C(1,1) == Approx(50));
}
