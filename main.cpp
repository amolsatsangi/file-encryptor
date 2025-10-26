#include<iostream>
#include<filesystem>
#include "./src/app/processes/ProcessManagement.hpp"
#include "./src/app/processes/Task.hpp"
#include "./src/app/fileHandling/IO.hpp"


namespace fs = std::filesystem;

int main(int argc, char * argv[]){

    std::string directory;
    std::string action;
    
    std::cout<<"Enter the directory path: "<<std::endl;
    std::getline(std::cin, directory);

    std::cout<<"Enter the action (encrypt/decrypt)"<<std::endl;
    std::getline(std::cin, action); 
    try {
        if(fs::exists(directory) && fs::is_directory(directory)){
            ProcessManagement Processmanagement;
            for(const auto &entry : fs::recursive_directory_iterator(directory)){
                if(entry.is_regular_file()){
                    std::string filePath = entry.path().string();
                    IO io(filePath);
                    std::fstream f_stream = std::move(io.getFileStream());
                    if(f_stream.is_open()){
                        Action taskAction = (action == "encrypt"?Action::ENCRYPT:Action::DECRYPT);
                        auto task = std::make_unique<Task> (std::move(f_stream),filePath, taskAction);
                        Processmanagement.submitToQueue(std::move(task));
                    }
                    else{
                        std::cout<<"Enable to open the file: "<<filePath<< std::endl;
                    }

                }
            }
            Processmanagement.executeTask();
        }
        else{
            std::cout<<"Invalid directory path: "<<directory<<std::endl;
        }

    }catch(const  fs::filesystem_error &ex){
        std::cout<<"Filesystem Error: "<<ex.what()<<std::endl;
    }

    return 0;
}
