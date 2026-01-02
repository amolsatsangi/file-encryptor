#include<iostream> 
#include<memory>
#include<cstring>
#include "../encryptDecrypt/Cryption.hpp"
#include "ProcessManagement.hpp"
#include "Task.hpp"

ProcessManagement::ProcessManagement(){
}
bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task){
    taskQueue.push(std::move(task));
    return true;
}
void ProcessManagement::executeTask(){
    while(!taskQueue.empty()){
        std::unique_ptr<Task> task_to_execute = std::move(taskQueue.front());
        taskQueue.pop();
        std::cout<<"Executing task: "<<task_to_execute->filePath<<std::endl;
        executeCryption(*task_to_execute);
    }
}
