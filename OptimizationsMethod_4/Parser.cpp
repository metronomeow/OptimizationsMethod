#include "Parser.h"
#include <iostream>


bool Parser::readFile( std::ifstream & fs, Graph &graph ) {
    size_t nodeCount; 
    size_t edgeCount;
    double reqTime;

    std::string buf;
    
    fs >> nodeCount;
    fs >> edgeCount;

    std::getline( fs, buf );
    if( !buf.empty() ) return false;

    if( !nodeCount ) return false;
    if( !edgeCount ) return false;

    for( size_t i = 0; i < nodeCount; i++ ) {
        int sym;
        fs >> sym;
        if( !graph.addNode( sym ) )  return false;
    }
    for( size_t i = 0; i < edgeCount; i++ ) {
        int n1, n2;
        double weight;
        fs >> n1 >> n2 >> weight;
        Node * node1 = graph.getNodeByName( n1 );
        if( !node1 )  return false;
        Node * node2 = graph.getNodeByName( n2 );
        if( !node2 )  return false;
        if( !graph.addEdge( node1, node2, weight ) )  return false;

    }
    
    return true;
}
bool Parser::isAllowedSymbol( int sym ) {
    
   /* if( sym == '.' ) return true;
    if( sym > 64 and sym < 91 ) return true;
    if( sym > 96 and sym < 123 ) return true;
    return false;*/
    return true;
}
