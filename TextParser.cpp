//
// Created by Emanuele Casciaro on 30/09/22.
//

#include "TextParser.h"


void TextParser::merge(std::map<std::string, size_t> &master, std::map<std::string, size_t> &slave) {
    for (auto iter = slave.begin(); iter != slave.end(); ++iter) {
        master[iter->first] += iter->second;
    }

}

void TextParser::mergeParallel(std::map<std::string, size_t> &master, std::map<std::string, size_t> &slave) {
#pragma omp parallel for
    for (auto iter = slave.begin(); iter != slave.end(); ++iter) {
        // there cannot be a data race condition, each element of a map is mapped on a different position in the master
        master[iter->first] += iter->second;
    }
}


TextParser::TextParser(size_t size) : ngramSize(size) {}

std::map<std::string, size_t> TextParser::parseText(const std::string &text) {
    auto result = std::map<std::string, size_t>();
    try {

        for (size_t i = 0; i < text.size() - ngramSize; i++) {
            auto substr = text.substr(i, ngramSize);
            // atomic step, more than one thread could update the same element
            result[substr]++;
        }
    } catch (std::out_of_range exception) {
        // printf("Out of Range exception at parseText\n");
    }
    return result;
}

std::map<std::string, size_t> TextParser::parseMultipleText(const std::vector<std::string> &texts) {
    auto result = std::map<std::string, size_t>();
    for (size_t i = 0; i < texts.size(); i++) {
        try {
            for (size_t j = 0; j < texts[i].size() - ngramSize; j++) {
                auto substr = texts[i].substr(j, ngramSize);
                // atomic step, more than one thread could update the same element
                result[substr]++;
            }

        } catch (std::out_of_range exception) {
            // printf("Out of Range exception at parseMultipleText\n");
        }
    }
    return result;
}

std::map<std::string, size_t> TextParser::parseTextParallel(const std::string &text) {
    auto result = std::map<std::string, size_t>();
#pragma omp parallel for
    for (size_t i = 0; i < text.size() - ngramSize; i++) {
        try {
            std::string substr = text.substr(i, ngramSize);
#pragma omp atomic
            // atomic step, more than one thread could update the same element
            result[substr]++;
        }
        catch (std::out_of_range exception) {
            // printf("Out of Range exception at parseTextParallel\n");
        }
    }


    return result;
}

std::map<std::string, size_t> TextParser::parseMultipleTextParallel(const std::vector<std::string> &texts) {
    auto result = std::map<std::string, size_t>();
#pragma omp parallel for
    for (size_t i = 0; i < texts.size(); i++) {
        try {

#pragma omp parallel for
            for (size_t j = 0; j < texts[i].size() - ngramSize; j++) {
                auto substr = texts[i].substr(j, ngramSize);
                // atomic step, more than one thread could update the same element
#pragma omp atomic
                result[substr]++;
            }
        } catch (std::out_of_range exception) {
            // printf("Out of Range exception at parseMultipleTextParallel\n");
        }
    }
    return result;
}
