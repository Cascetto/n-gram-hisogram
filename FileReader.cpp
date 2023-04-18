//
// Created by Emanuele Casciaro on 29/09/22.
//

#include "FileReader.h"

FileReader::FileReader(std::string path) : path(std::move(path)){

}

void FileReader::setPath(const std::string &newPath) {
    FileReader::path = newPath;
}

std::vector<std::string> FileReader::read(float percentage) {
    auto result = std::vector<std::string>();
    for(auto& entry : std::filesystem::directory_iterator(path)){
        std::ifstream file(entry.path(), std::ios::binary | std::ios::ate);
        std::streamsize size = file.tellg();
        char* buffer = (char*) malloc(sizeof(char) * size * percentage);
        file.seekg(0, std::ios::beg);
        file.read(buffer, size * percentage);
        file.close();
        result.emplace_back(std::string(buffer));
    }
    return result;
}

std::string FileReader::readWhole(float percentage) {
    std::string result = std::string();
    for(auto& entry : std::filesystem::directory_iterator(path)) {
        std::ifstream file(entry.path(), std::ios::binary | std::ios::ate);
        std::streamsize size = file.tellg();
        char* buffer = (char*) malloc(sizeof(char) * size * percentage);
        file.seekg(0, std::ios::beg);
        file.read(buffer, size * percentage);
        file.close();
        result += std::string(buffer);
    }
    return result;
}


std::vector<std::string> FileReader::readParallel(float percentage) {
    auto result = std::vector<std::string>();
    auto diter = std::filesystem::directory_iterator(path);
#pragma omp parallel for
    for(auto iter = begin(diter); iter != end(diter); iter++){
        std::ifstream file(iter->path(), std::ios::binary | std::ios::ate);
        std::streamsize size = file.tellg();
        char* buffer = (char*) malloc(sizeof(char) * size * percentage);
        file.seekg(0, std::ios::beg);
        file.read(buffer, size * percentage);
#pragma omp atomic
        result.emplace_back(std::string(buffer));
    }
    return result;
}

std::string FileReader::readParallelWhole(float percentage) {
    std::string result = std::string();
    auto diter = std::filesystem::directory_iterator(path);
#pragma omp parallel for reduce(+: result)
    for(auto iter = begin(diter); iter != end(diter); iter++){
        std::ifstream file(iter->path(), std::ios::binary | std::ios::ate);
        std::streamsize size = file.tellg();
        char* buffer = (char*) malloc(sizeof(char) * size * percentage);
        file.seekg(0, std::ios::beg);
        file.read(buffer, size * percentage);
        result += std::string(buffer);
    }
    return result;
}