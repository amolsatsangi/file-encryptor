#include<iostream>
#include "IO.hpp"

IO::IO(const std::string &filePath){
    fileStream.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if(!fileStream.is_open()){
        std::cout<<"Unable to open the file: "<<filePath<<std::endl;
    }
}

std::fstream IO:: getFileStream(){
    return std::move(fileStream);
}

IO::~IO(){
    if(fileStream.is_open())
        fileStream.close();
}