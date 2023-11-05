/*
** EPITECH PROJECT, 2023
** ThreadPool
** File description:
** ThreadPool.cpp
*/

#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t numThreads) : stop(false)
{
  for (size_t i = 0; i < numThreads; ++i)
  {
    workers.emplace_back([this]
                         {
      while (true) {
        std::function<void()> task;
        {
          std::unique_lock<std::mutex> lock(queueMutex);
          condition.wait(lock, [this] { return stop || !tasks.empty(); });
          if (stop && tasks.empty()) {
              return;
          }
          task = std::move(tasks.front());
          tasks.pop();
        }
        task();
      } });
  }
}

ThreadPool::~ThreadPool()
{
  {
    std::unique_lock<std::mutex> lock(queueMutex);
    stop = true;
  }

  condition.notify_all();

  for (std::thread &worker : workers)
  {
    worker.join();
  }
  std::cout << "destroyed thread pool" << std::endl;
}

void ThreadPool::addThread()
{
  workers.emplace_back([this]
                       {
      while (true) {
        std::function<void()> task;
        {
          std::unique_lock<std::mutex> lock(queueMutex);
          condition.wait(lock, [this] { return stop || !tasks.empty(); });
          if (stop && tasks.empty()) {
              return;
          }
          task = std::move(tasks.front());
          tasks.pop();
        }
        task();
      } });
}