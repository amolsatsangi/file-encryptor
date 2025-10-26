#ifndef IO_HPP
#define IO_HPP
#include<string>
#include<fstream>
#include<vector>    
#include<iostream>

class IO{
    private:
        std::fstream fileStream;
        std::string filePath;
    public:
        IO(const std::string &filePath);
        ~IO();
        std::fstream getFileStream();      

};

#endif