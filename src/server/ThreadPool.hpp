/*
** EPITECH PROJECT, 2023
** ThreadPool
** File description:
** ThreadPool.hpp
*/

#ifndef HEADER_THREADPOOL
#define HEADER_THREADPOOL
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>

class ThreadPool {
  public:
    ThreadPool(size_t numThreads);
     ~ThreadPool();
     template <class F>
     void enqueue(F &&f)
     {
       {
         std::unique_lock<std::mutex> lock(queueMutex);
         tasks.emplace(std::forward<F>(f));
       }

       condition.notify_one();
     }

  protected:
  private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;

    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};

#endif /* !HEADER_THREADPOOL */
