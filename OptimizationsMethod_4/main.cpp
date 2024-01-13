#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include <vector>
#include "Parser.h"

std::string help =
R"("
# Methods of Optimization, BDZ4 by Mikhaylova Ekaterina #
  > find minimum spanning tree
  > find pruferr sequence
  for graph #7:
  x2 ---6--- x1 ---2--- x6
  |\         /\         /|
  | \       /  \       / |
  |  4     2    3     /  |
  |   \   /      \___/_  5
  |    \ /          |  | |
  2     /\          3  | |
  |    /  \         |  | |
  |   /    \________|___\x5
  |  /              |
  x3______3_________x4
)";

std::string strGraph =
R"(6 9
1
2
3
4
5
6
1 2 6
1 3 2
1 5 3
1 6 2
2 3 2
2 5 4
3 4 3
4 6 3
5 6 5
)";

//.............................................................................
#define EXIT( message ) { std::cout << "\033[1;31mERROR: " << message << " \033[0m" << std::endl; exit(EXIT_FAILURE); }
#define WARNING( message ) { std::cout << "\033[1;33mWARNING: " << message << " \033[0m" << std::endl; }
#define INFO( message ) { std::cout << "\033[1;32mINFO: " << message << " \033[0m" << std::endl; }


//.............................................................................
int main( int ac, char * av[] ) {


    if( ac > 1 ) if( !strcmp( av[ 1 ], "--help" ) ) {
        std::cout << help;
        return EXIT_SUCCESS;
    }
    std::ofstream f( "myGraph.txt" );
    f << strGraph;
    f.close();
    std::ifstream readF( "myGraph.txt" );
    Parser pars;
    Graph graph;
    pars.readFile( readF, graph );
    readF.close();
    std::cout << "Source graph:" << std::endl;
    graph.print(std::cout);
    
    Graph span;
    std::cout << "Minnimum spanning tree:" << std::endl;
    graph.findSpanningTree(span);
    span.print(std::cout);
    std::cout << "Prufer:" << std::endl;
    span.findPrufer();

    return EXIT_SUCCESS;
}