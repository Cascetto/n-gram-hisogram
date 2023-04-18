#include <iostream>
#include <map>
#include <sys/time.h>
#include "FileReader.h"
#include "TextParser.h"

int main() {
    size_t numberOfIterations = 1;
    size_t i = 3;
    FileReader fr = FileReader("./source");
        TextParser tp = TextParser(i);

        auto begin = std::chrono::high_resolution_clock::now();
            // std::cout << "Iteration #" << i << std::endl;
            std::string text = fr.readWhole();
            std::map<std::string, size_t> m = tp.parseText(text);
           auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        auto totalTime = elapsed.count() * 1e-9f;
        printf("Serial Mode Configuration: #IT=%lu, N=%d Time measured: %.3f seconds, %.5f per iteration.\n", numberOfIterations, i, totalTime, totalTime / numberOfIterations);

        begin = std::chrono::high_resolution_clock::now();
            // std::cout << "Iteration #" << i << std::endl;
            std::vector<std::string> texts = fr.read();
            std::map<std::string, size_t> m1 = tp.parseMultipleText(texts);
        end = std::chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        totalTime = elapsed.count() * 1e-9f;
        printf("Serial Mode (multiple) Configuration: #IT=%lu, N=%d, Time measured: %.3f seconds, %.5f per iteration.\n", numberOfIterations, i, totalTime, totalTime / numberOfIterations);

        begin = std::chrono::high_resolution_clock::now();
            // std::cout << "Iteration #" << i << std::endl;
            text = fr.readParallelWhole();
            std::map<std::string, size_t> m2 = tp.parseTextParallel(text);
        end = std::chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        totalTime = elapsed.count() * 1e-9f;
        printf("Parallel Mode Configuration: #IT=%lu, N=%d Time measured: %.3f seconds, %.5f per iteration.\n", numberOfIterations, i, totalTime, totalTime / numberOfIterations);
        begin = std::chrono::high_resolution_clock::now();
            // std::cout << "Iteration #" << i << std::endl;
            texts = fr.readParallel();
            std::map<std::string, size_t> m3 = tp.parseMultipleTextParallel(texts);
        end = std::chrono::high_resolution_clock::now();
        elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
        totalTime = elapsed.count() * 1e-9f;
        printf("Parallel Mode (multiple) Configuration: #IT=%lu, N=%d Time measured: %.3f seconds, %.5f per iteration.\n", numberOfIterations, i, totalTime, totalTime / numberOfIterations);


        printf("Count of 'cia' istances:\nSerial\t%lu\nSerial multiple\t%lu\nParallel\t%lu\nParallel Multiple\t%lu",
               m["cia"], m1["cia"], m2["cia"], m3["cia"]);
}
