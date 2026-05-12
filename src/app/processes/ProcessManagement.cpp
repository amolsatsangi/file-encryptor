#include<iostream> 
#include<memory>
#include<cstring>
#include "../encryptDecrypt/Cryption.hpp"
#include "ProcessManagement.hpp"
#include "Task.hpp"
#include<filesystem>
#include<mutex>
#include<thread>

namespace fs = std::filesystem;
ProcessManagement::ProcessManagement() : complete_production{false}{
}
bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task){
    taskQueue.push(std::move(task));
    return true;
}
void ProcessManagement::executeTask(){
    while(true){
        std::unique_lock<std::mutex> q_lock(q_mtx);
        cv.wait(q_lock,[this]{return !taskQueue.empty() || complete_production;});
        if(taskQueue.empty() && complete_production){
            q_lock.unlock();
            break;
        }
        try{
            auto task_to_execute = std::move(taskQueue.front());
            taskQueue.pop();
            q_lock.unlock();
            {
                std::lock_guard<std::mutex> log_lock(log_mtx);
                std::cout<<"Thread "<<std::this_thread::get_id()<<"Executing task: "<<task_to_execute->filePath<<std::endl;
            }
                executeCrypto(*task_to_execute);
            }
        catch (const std::exception &ex){
            std::lock_guard<std::mutex> log_lock(log_mtx);
            std::cout<< "Thread "<< std::this_thread::get_id()<< " Error: "<< ex.what()<< std::endl;
        }
        
    }
}
void ProcessManagement::populateTasks(const std::string & directory,const std::string & action){
    for(const auto &entry : fs::recursive_directory_iterator(directory)){
        if(entry.is_regular_file()){
            std::string filePath = entry.path().string();
            IO io(filePath);
            std::fstream f_stream = std::move(io.getFileStream());
            if(f_stream.is_open()){
                Action taskAction = (action == "encrypt"?Action::ENCRYPT:Action::DECRYPT);
                auto task = std::make_unique<Task> (std::move(f_stream),filePath, taskAction);
                {
                    std::lock_guard<std::mutex> q_lock(q_mtx);
                    this->submitToQueue(std::move(task));
                }
                cv.notify_one();
            }
            else{
                std::cout<<"Enable to open the file: "<<filePath<< std::endl;
            }
        }
    }
    {
        std::lock_guard<std::mutex> q_lock(q_mtx);
        complete_production = true;
    }
    cv.notify_all();
}
