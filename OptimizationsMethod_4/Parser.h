#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Graph.h"

class Parser {
public:
    bool readFile( std::ifstream & fs, Graph & graph );  

private:
    bool isAllowedSymbol( int sym );

};

