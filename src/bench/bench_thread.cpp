#include <iostream>
#include <chrono>
#include "../../include/utec/nn/dense.h"
#include "../../include/utec/threading/ThreadPool.h"

using namespace utec::neural_network;
using namespace utec::threading;
using reloj = std::chrono::high_resolution_clock;

template <typename T>
class DenseParalela : public Dense<T> {
    static ThreadPool pool;
public:
    using Dense<T>::Dense;

    Tensor<T,2> forward(const Tensor<T,2>& X) override {
        const std::size_t lote  = X.shape()[0];
        const std::size_t chunk = (lote + pool.size()-1)/pool.size();
        Tensor<T,2> out({lote, this->b.shape()[1]});
        std::vector<std::future<void>> futs;

        for (std::size_t i = 0; i < lote; i += chunk) {
            std::size_t i_fin = std::min(i + chunk, lote);
            futs.push_back(pool.submit([&,i,i_fin]{
                Tensor<T,2> sub({i_fin-i, X.shape()[1]});
                for(std::size_t r=i; r<i_fin; ++r)
                    for(std::size_t c=0;c<X.shape()[1];++c)
                        sub(r-i,c)=X(r,c);
                auto parc = Dense<T>::forward(sub);
                for(std::size_t r=i; r<i_fin; ++r)
                    for(std::size_t c=0;c<parc.shape()[1];++c)
                        out(r,c)=parc(r-i,c);
            }));
        }
        for(auto& f:futs) f.get();
        return out;
    }
};
/* define pool (4 hilos) */
template<typename T> ThreadPool DenseParalela<T>::pool(4);

int main() {
    constexpr std::size_t batch = 10'000;
    constexpr std::size_t in_f  = 128;
    constexpr std::size_t out_f = 256;

    DenseParalela<float> capa(in_f,out_f,
        [](auto& W){ W.fill(0.01f); },
        [](auto& b){ b.fill(0.0f); });

    Tensor<float,2> X({batch,in_f});
    for (auto& v : X) v = 0.5f;

    auto t0 = reloj::now();
    auto Y  = capa.forward(X);
    auto t1 = reloj::now();

    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count();
    std::cout << "ThreadPool x4: " << ms << " ms\n";
    std::cout << "Y(0,0) = " << Y(0,0) << "\n";
}
