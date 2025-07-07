#include "../../../include/utec/threading/ThreadPool.h"

using namespace utec::threading;

ThreadPool::ThreadPool(std::size_t n_hilos) {
    if (n_hilos == 0) n_hilos = 1;
    for (std::size_t i = 0; i < n_hilos; ++i) {
        _workers.emplace_back([this]{
            while (true) {
                std::function<void()> tarea;
                {   /* toma tarea */
                    std::unique_lock<std::mutex> lock(_m);
                    _cv.wait(lock, [this]{ return _stop || !_cola.empty(); });
                    if (_stop && _cola.empty()) return;
                    tarea = std::move(_cola.front());
                    _cola.pop();
                }
                tarea();
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    {   /* pedir parada */
        std::unique_lock<std::mutex> lock(_m);
        _stop = true;
    }
    _cv.notify_all();
    for (auto& h : _workers) h.join();
}

std::size_t ThreadPool::size() const noexcept {
    return _workers.size();
}
