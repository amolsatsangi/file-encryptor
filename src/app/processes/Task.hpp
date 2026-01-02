#ifndef TASK_HPP
#define TASK_HPP

#include<iostream>
#include<string>
#include<fstream>
#include "../fileHandling/IO.hpp"

enum class Action{
    ENCRYPT,
    DECRYPT
};

class Task{
    public:
        std::string filePath;
        std::fstream f_stream;
        Action action;

        Task(std::fstream && f_str,std::string fp,  Action act):
            f_stream{std::move(f_str)},filePath{fp},action{act}{}
}; 


#endif