#ifndef UTEC_NN_NEURAL_NETWORK_H
#define UTEC_NN_NEURAL_NETWORK_H

#include "nn_interfaces.h"
#include <vector>
#include <memory>
#include <random>
#include <algorithm>
#include <array>            // ← NUEVO
#include "nn_loss.h"
#include "nn_optimizer.h"   // ← NUEVO

using utec::algebra::Tensor;

namespace utec::neural_network {

template <typename T>
class NeuralNetwork {
private:
    std::vector<std::unique_ptr<ILayer<T>>> layers;

public:
    /* ---------- gestión de capas ---------- */
    void add_layer(std::unique_ptr<ILayer<T>> layer) {
        layers.emplace_back(std::move(layer));
    }

    /* ---------- forward ---------- */
    Tensor<T,2> forward(const Tensor<T,2>& x) {
        Tensor<T,2> out = x;
        for (auto& layer : layers) out = layer->forward(out);
        return out;
    }

    /* ---------- backward ---------- */
    void backward(const Tensor<T,2>& grad) {
        Tensor<T,2> g = grad;
        for (auto it = layers.rbegin(); it != layers.rend(); ++it)
            g = (*it)->backward(g);
    }

    /* ---------- update de parámetros ---------- */
    void optimize(IOptimizer<T>& optimizer) {
        for (auto& layer : layers) layer->update_params(optimizer);
    }

    /* ============================================================
     *  train  (versión completa: se indica LossType y OptimizerType)
     * ============================================================*/
    template <template <typename, size_t> class LossType,
              template <typename>          class OptimizerType>
    void train(const Tensor<T,2>& X, const Tensor<T,2>& Y,
               size_t epochs, size_t batch_size, T learning_rate)
    {
        OptimizerType<T> optimizer(learning_rate);

        for (size_t epoch = 0; epoch < epochs; ++epoch) {
            for (size_t i = 0; i < X.shape()[0]; i += batch_size) {
                size_t b = std::min(batch_size, X.shape()[0] - i);

                Tensor<T,2> xb(std::array<size_t,2>{ b, X.shape()[1] });
                Tensor<T,2> yb(std::array<size_t,2>{ b, Y.shape()[1] });

                /* copiar lote */
                for (size_t k = 0; k < b; ++k) {
                    size_t idx = i + k;
                    for (size_t j = 0; j < X.shape()[1]; ++j)
                        xb(k,j) = X(idx,j);
                    for (size_t j = 0; j < Y.shape()[1]; ++j)
                        yb(k,j) = Y(idx,j);
                }

                /* forward → loss → backward → update */
                Tensor<T,2> y_pred = forward(xb);
                LossType<T,2> loss(y_pred, yb);

                Tensor<T,2> grad = loss.loss_gradient();
                backward(grad);

                optimizer.step();   // (inofensivo en SGD/Adam)
                optimize(optimizer);
            }
        }
    }

    /* ============================================================
     *  train  (wrapper: se indica solo LossType, usa SGD por defecto)
     * ============================================================*/
    template <template <typename, size_t> class LossType>
    void train(const Tensor<T,2>& X, const Tensor<T,2>& Y,
               size_t epochs, size_t batch_size, T learning_rate)
    {
        train<LossType, SGD>(X, Y, epochs, batch_size, learning_rate);
    }

    /* ---------- inferencia ---------- */
    Tensor<T,2> predict(const Tensor<T,2>& X) { return forward(X); }
};

} // namespace utec::neural_network

#endif // UTEC_NN_NEURAL_NETWORK_H