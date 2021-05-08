//
// Created by Бушев Дмитрий on 08.05.2021.
//

#include "FileToGraphParser.h"
#include <cassert>
#include <iostream>


#define ASSERT_OPEN(X) assert(X.is_open() && "input file must be open")
enum class ParseState{OK, FAIL, END};

struct ParseInfo{
    ParseState state;
    std::string what;
    operator bool() const{
        return state != ParseState::OK;
    }
};

bool isSpace(char c){
    return c == ' ';
}

void skipSpaces(std::ifstream& input){
    ASSERT_OPEN(input);
    while(true){
        char c = input.get();
        if(input.eof())
            return;
        if(!isSpace(c)) {
            input.seekg(-1, std::ios::cur);
            break;
        }
    }
}
bool isNumeral(char c, int* ret){
    if(c >= '0' && c <= '9'){
        *ret = c - '0';
        return true;
    }
    return false;
}

void printFailMessage(std::ifstream& input, std::string const& what) {
    size_t pos = input.tellg();
    input.seekg(0);
    std::string input_seq;
    input_seq.resize(pos + 1);
    std::string blank;
    blank.resize(pos, ' ');
    input.get(input_seq.data(), pos + 1);
    std::cout << "Error(" << pos <<"): " << what << std::endl;
    std::cout << input_seq << std::endl << blank <<  "^ here" << std::endl;
}

#define MATCH_INTEGER(X, I)  if(auto info = matchInteger(X, &I)){ return info; }
#define CHECK_EOF(X)         if(X.bad()){ return {ParseState::FAIL, "Unexpected end of file"};}


ParseInfo matchInteger(std::ifstream& input, int* num){
    ASSERT_OPEN(input);
    char c;
    int ret = 0;
    bool matched_numeral = false, matched_sign = false;
    while(true){
        c = input.get();
        int num_c;

        CHECK_EOF(input)

        if(c == '-'){
            if(matched_numeral || matched_sign)
                break;
            matched_sign = true;
        } else if(isNumeral(c, &num_c)){
            ret *= 10;
            ret += num_c;
            matched_numeral = true;
        } else
            break;
    }

    if(!matched_numeral)
        return {ParseState::FAIL, "Syntax error"};

    if(matched_sign){
        ret *= -1;
    }
    input.seekg(-1, std::ios::cur);
    *num = ret;
    return {ParseState::OK, ""};
}

ParseInfo parsePerVertex(std::ifstream& input, Graph& graph) {
    ASSERT_OPEN(input);
    skipSpaces(input);
    if(input.eof()){
        return {ParseState::END, ""};
    }
    int vertId;

    MATCH_INTEGER(input, vertId)


    graph.addVertex(vertId);

    char c;
    c = input.get();

    CHECK_EOF(input)

    if(c != ':')
        return {ParseState::FAIL, "Syntax error"};

    while(true){
        skipSpaces(input);
        c = input.get();

        CHECK_EOF(input)

        if(c == ';')
            break;
        else
            input.seekg(-1, std::ios::cur);

        int anotherId;

        MATCH_INTEGER(input, anotherId)

        skipSpaces(input);

        c = input.get();

        CHECK_EOF(input)

        if(c == '('){
            int weight;
            MATCH_INTEGER(input, weight)
            graph.addEdge(vertId, anotherId, weight);
            c = input.get();

            CHECK_EOF(input)
            if(c == ')')
                continue;
            else{
                return {ParseState::FAIL, "Syntax error"};
            }
        }else{
            return {ParseState::FAIL, "Syntax error"};
        }
    }

    return {ParseState::OK, ""};
}

bool parseFile(std::ifstream& input, Graph& graph){
    ASSERT_OPEN(input);

    input.seekg(0);
    ParseInfo info = {ParseState::OK, ""};
    while(info.state == ParseState::OK){
        info = parsePerVertex(input, graph);
    }

    if(info.state == ParseState::FAIL){
        printFailMessage(input, info.what);
        return false;
    }
    return true;
}
