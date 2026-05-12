#include<iostream>
#include<filesystem>
#include "./src/app/processes/ProcessManagement.hpp"
#include "./src/app/processes/Task.hpp"
#include "./src/app/fileHandling/IO.hpp"
#include<thread>
#include<algorithm>
namespace fs = std::filesystem;

int main(int argc, char * argv[]){

    std::string directory;
    std::string action;
    
    std::cout<<"Enter the directory path: "<<std::endl;
    std::getline(std::cin, directory);

    std::cout<<"Enter the action (encrypt/decrypt)"<<std::endl;
    std::getline(std::cin, action);
    int number_of_threads = std::max(2,static_cast<int>(std::thread::hardware_concurrency())-1);
    try {
        if(fs::exists(directory) && fs::is_directory(directory)){
            ProcessManagement Processmanagement;
            try{
                std::thread master( &ProcessManagement::populateTasks,&Processmanagement,directory,action);
                std::vector<std::thread> consumer_thread;
                for(int i=0;i<number_of_threads;i++){
                    consumer_thread.emplace_back( &ProcessManagement::executeTask,&Processmanagement);
                }
                master.join();
                for(int i=0;i<number_of_threads;i++){
                    consumer_thread[i].join();
                }
            }
            catch(const std::exception& ex){
                std::cout<<"Not able to create the thread"<<std::endl;
                std::cout<<ex.what()<<std::endl;
                return 1;
            } 
        }
        else{
            std::cout<<"Invalid directory path: "<<directory<<std::endl;
        }

    }catch(const  fs::filesystem_error &ex){
        std::cout<<"Filesystem Error: "<<ex.what()<<std::endl;
    }

    return 0;
}
