cmake_minimum_required(VERSION 3.23)
project(NGRAM)

set(CMAKE_CXX_STANDARD 17)
# set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
add_executable(NGRAM main.cpp FileReader.cpp TextParser.cpp)
