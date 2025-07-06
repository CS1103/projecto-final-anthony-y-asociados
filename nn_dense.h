#ifndef UTEC_NN_DENSE_H
#define UTEC_NN_DENSE_H

#include "nn_interfaces.h"
#include <memory>

using utec::algebra::Tensor;

namespace utec::neural_network {

template <typename T>
class Dense final : public ILayer<T> {
private:
    Tensor<T,2> W, dW;          // [in, out]
    Tensor<T,2> b, db;          // [1, out]  ✅ ahora 2-D
    Tensor<T,2> last_input;     // cache

public:
    template <typename InitWFun, typename InitBFun>
    Dense(size_t in_f, size_t out_f,
          InitWFun init_w, InitBFun init_b)
            : W ( Tensor<T,2>( std::array<size_t,2>{in_f, out_f} ) )
            , dW( Tensor<T,2>( std::array<size_t,2>{in_f, out_f} ) )
            , b ( Tensor<T,2>( std::array<size_t,2>{1   , out_f} ) )
            , db( Tensor<T,2>( std::array<size_t,2>{1   , out_f} ) )
    {
        init_w(W);   // lambda acepta Tensor<…,2>&
        init_b(b);   // idem para bias
    }

    // ---------- forward ----------
    Tensor<T,2> forward(const Tensor<T,2>& x) override {
        last_input = x;                                // B × in
        Tensor<T,2> out = utec::algebra::matrix_product(x, W); // B × out
        for (size_t i = 0; i < out.shape()[0]; ++i)
            for (size_t j = 0; j < out.shape()[1]; ++j)
                out(i,j) += b(0,j);                    // broadcast bias
        return out;
    }

    // ---------- backward ----------
    Tensor<T,2> backward(const Tensor<T,2>& dZ) override {
        // dW = Xᵀ · dZ
        dW = utec::algebra::matrix_product(
                 utec::algebra::transpose_2d(last_input), dZ);

        // db = sum rows of dZ
        db.fill(0);
        for (size_t i = 0; i < dZ.shape()[0]; ++i)
            for (size_t j = 0; j < dZ.shape()[1]; ++j)
                db(0,j) += dZ(i,j);

        // dX = dZ · Wᵀ
        return utec::algebra::matrix_product(
                   dZ, utec::algebra::transpose_2d(W));
    }

    // ---------- update ----------
    void update_params(IOptimizer<T>& opt) override {
        opt.update(W,  dW);
        opt.update(b,  db);     // ✅ ya no convierte a 1-D
    }
};

} // namespace utec::neural_network

#endif // UTEC_NN_DENSE_H