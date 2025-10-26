#ifndef TASK_HPP
#define TASK_HPP

#include<iostream>
#include<string>
#include<fstream>
#include "../fileHandling/IO.hpp"
#include<sstream>

enum class Action{
    ENCRYPT,
    DECRYPT
};

struct Task{
    std::string filePath;
    std::fstream f_stream;
    Action action;

    Task(std::fstream && f_str,std::string fp,  Action act):
        f_stream{std::move(f_str)},filePath{fp},action{act}{}
    
    std::string toString(){
        std::ostringstream oss;
        oss<<filePath<<","<<(action==Action::ENCRYPT?"ENCRYPT":"DECRYPT");
        //"test.txt","ENCRYPT"
        return oss.str();
    }
    static Task fromString(const std::string &taskData){
        std::istringstream iss(taskData);
        std::string filePath;
        std::string actionStr;

        if(std::getline(iss,filePath,',') && std::getline(iss,actionStr)){
            Action action = (actionStr == "ENCRYPT"?Action::ENCRYPT: Action::DECRYPT);
            IO io(filePath);
            std::fstream f_stream = std::move(io.getFileStream());
            if(f_stream.is_open()){
                return Task(std::move(f_stream),filePath,action);
            }
            else{
                throw std::runtime_error("Failed to open file: "+ filePath);
            }
        }
        else{
            throw std::runtime_error("Invalid Task format");
        }
    }
}; 


#endif