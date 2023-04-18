//
// Created by Emanuele Casciaro on 29/09/22.
//

#ifndef NGRAMOPENMPPLAYGROUND_FILEREADER_H
#define NGRAMOPENMPPLAYGROUND_FILEREADER_H

#include <string>
#include <vector>
#include <iostream>
#include <filesystem>
#include <fstream>

class FileReader {

public:
    explicit FileReader(std::string path);
    std::vector<std::string> read(float size = 1);
    std::string readWhole(float size = 1);
    std::vector<std::string> readParallel(float size = 1);
    std::string readParallelWhole(float size = 1);

    void setPath(const std::string &path);

private:
    std::string path;

};


#endif //NGRAMOPENMPPLAYGROUND_FILEREADER_H
