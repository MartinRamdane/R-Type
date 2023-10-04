/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** ThreadSafeQueue
*/

#ifndef THREADSAFEQUEUE_HPP_
#define THREADSAFEQUEUE_HPP_
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class ThreadSafeQueue
{
public:
    ThreadSafeQueue() = default;
    ThreadSafeQueue(const ThreadSafeQueue<T> &) = delete;
    virtual ~ThreadSafeQueue() { clear(); };

    const T &front()
    {
        std::scoped_lock lock(_mutex);
        return _queue.front();
    }
    const T &back()
    {
        std::scoped_lock lock(_mutex);
        return _queue.back();
    }
    T pop_front()
    {
        std::scoped_lock lock(_mutex);
        auto t = std::move(_queue.front());
        _queue.pop_front();
        return t;
    }
    T pop_back()
    {
        std::scoped_lock lock(_mutex);
        auto t = std::move(_queue.back());
        _queue.pop_back();
        return t;
    }
    void push_back(const T &item)
    {
        std::scoped_lock lock(_mutex);
        _queue.push_back(std::move(item));
        std::unique_lock<std::mutex> ul(muxBlocking);
        _cond.notify_one();
    }
    void push_front(const T &item)
    {
        std::scoped_lock lock(_mutex);
        _queue.push_front(std::move(item));
        std::unique_lock<std::mutex> ul(muxBlocking);
        _cond.notify_one();
    }
    bool empty()
    {
        std::scoped_lock lock(_mutex);
        return _queue.empty();
    }
    size_t count()
    {
        std::scoped_lock lock(_mutex);
        return _queue.size();
    }
    void clear()
    {
        std::scoped_lock lock(_mutex);
        _queue.clear();
    }
    void wait()
    {
        while (empty())
        {
            std::unique_lock<std::mutex> ul(muxBlocking);
            _cond.wait(ul);
        }
    }

protected:
    std::mutex _mutex;
    std::deque<T> _queue;
    std::condition_variable _cond;
    std::mutex muxBlocking;

private:
};

#endif /* !THREADSAFEQUEUE_HPP_ */