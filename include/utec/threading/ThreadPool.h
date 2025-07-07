#ifndef UTEC_THREADING_THREADPOOL_H
#define UTEC_THREADING_THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <future>
#include <functional>
#include <condition_variable>
#include <type_traits>

namespace utec::threading {

class ThreadPool {
private:
    std::vector<std::thread>              _workers;
    std::queue<std::function<void()>>     _cola;
    std::mutex                            _m;
    std::condition_variable               _cv;
    bool                                  _stop{false};

public:
    explicit ThreadPool(std::size_t n_hilos = std::thread::hardware_concurrency());
    ~ThreadPool();

    std::size_t size() const noexcept;

    template <typename F, typename... Args>
    auto submit(F&& f, Args&&... args)
        -> std::future<std::invoke_result_t<F, Args...>>
    {
        using Ret = std::invoke_result_t<F, Args...>;
        auto tarea = std::make_shared<std::packaged_task<Ret()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<Ret> fut = tarea->get_future();

        {   /* scope de lock */
            std::unique_lock<std::mutex> lock(_m);
            if (_stop)
                throw std::runtime_error("ThreadPool detenido");
            _cola.emplace([tarea]{ (*tarea)(); });
        }
        _cv.notify_one();
        return fut;
    }
};

} // namespace utec::threading
#endif /* UTEC_THREADING_THREADPOOL_H */
