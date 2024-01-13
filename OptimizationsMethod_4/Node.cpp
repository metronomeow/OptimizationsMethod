#include "Node.h"

Node::Node( int sym ) : name(sym) {}

void Node::addFromEdge( Edge * from ) {
    if(from) fromEdge.push_back( from );
}

void Node::addToEdge( Edge * to ) {
    if(to) toEdge.push_back( to );
}

void Node::removeEdge( Edge * e ) {
    for( size_t i = 0; i < fromEdge.size(); i++ ) if( fromEdge[ i ] == e ) fromEdge.erase( fromEdge.begin() + i );
    for( size_t i = 0; i < toEdge.size(); i++ ) if( toEdge[ i ] == e ) toEdge.erase( toEdge.begin() + i );
}

std::ostream & operator<<( std::ostream & os, Node node ) {
    os << node.name;
    return os;
}
