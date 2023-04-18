//
// Created by Emanuele Casciaro on 30/09/22.
//

#ifndef NGRAMOPENMPPLAYGROUND_TEXTPARSER_H
#define NGRAMOPENMPPLAYGROUND_TEXTPARSER_H

#include <string>
#include <vector>
#include <map>

class TextParser {
public:
    explicit TextParser(size_t size);

    std::map<std::string, size_t> parseText(const std::string& text);
    std::map<std::string, size_t> parseMultipleText(const std::vector<std::string>& texts);
    std::map<std::string, size_t> parseTextParallel(const std::string& text);
    std::map<std::string, size_t> parseMultipleTextParallel(const std::vector<std::string>& texts);
private:
    size_t ngramSize;
    static void merge(std::map<std::string, size_t>& master, std::map<std::string, size_t>& slave);
    static void mergeParallel(std::map<std::string, size_t>& master, std::map<std::string, size_t>& slave);
};


#endif //NGRAMOPENMPPLAYGROUND_TEXTPARSER_H
