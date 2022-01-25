#include "zw_pipeline.hpp"
#include <fstream>
#include <iostream>
namespace zw{
     ZWPipeline::ZWPipeline(const std::string & vertFilepath,const std::string & fragFilepath){
        this->createGraphicsPipeline(vertFilepath,fragFilepath);
    }
    std::vector<char> ZWPipeline::readFile(const std::string& filename){
        std::ifstream file{filename,std::ios::ate|std::ios::binary};
        if(!file.is_open()){
            throw std::runtime_error("failed to open file: "+ filename);
        }
        size_t fileSize = (size_t)file.tellg();
        std::vector<char> buffer(fileSize);
        file.seekg(0);
        file.read(buffer.data(),fileSize);
        file.close();
        return buffer;
    }
    void ZWPipeline::createGraphicsPipeline(const std::string & vertFilepath,const std::string & fragFilepath){
        auto vertCode = this->readFile(vertFilepath);
        auto fragCode = this->readFile(fragFilepath);
        std::cout << "Vertex Shader Code Size: " << vertCode.size() << "\n";
        std::cout << "Fragment Shader Code Size: " << fragCode.size() << "\n";
    }
}