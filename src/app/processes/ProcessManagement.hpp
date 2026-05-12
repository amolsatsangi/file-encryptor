#ifndef PROCESS_MANAGEMENT_HPP
#define PROCESS_MANAGEMENT_HPP

#include "Task.hpp"
#include <queue>
#include<memory> 
#include<mutex>
#include<condition_variable>
class ProcessManagement{
    public:
        ProcessManagement();
        bool submitToQueue(std::unique_ptr<Task> task);
        void executeTask();
        void populateTasks(const std::string &,const std::string &);
    private:
        std::queue<std::unique_ptr<Task>> taskQueue;
        std::mutex q_mtx;
        std::mutex log_mtx;
        bool complete_production;
        std::condition_variable cv;

};

#endif