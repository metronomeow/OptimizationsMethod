#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <set>

std::set<int> collectedNode;

Graph::~Graph() {
    clear();
}
//..........................................................................................
void Graph::clear() {
    for( auto n : nodes ) delete n;
    for( auto e : edges ) delete e;
    nodes.clear();
    edges.clear();
    nodesMap.clear();
    
}
//..........................................................................................
bool Graph::addNode( int sym ) {
    if( nodesMap.find( sym ) != nodesMap.end() ) return false;
    Node * node = new Node( sym );
    nodes.push_back( node );
    nodesMap[ sym ] = node;
    return true;
}
//..........................................................................................

bool Graph::addEdge( Node * fromNode, Node * toNode, double w ) {
    if( !fromNode ) return false;
    if( !toNode ) return false;
    Edge * edge = new Edge( fromNode, toNode, w );
    edges.push_back( edge );
    fromNode->addToEdge( edge );
    toNode->addFromEdge( edge );
    return true;
}
//..........................................................................................
bool Graph::addUniqEdge( Edge * e ) {
    if( !e ) return false;
    if( !getNodeByName( e->getFromNode()->getName() ) ) addNode( e->getFromNode()->getName() );
    if( !getNodeByName( e->getToNode()->getName() ) ) addNode( e->getToNode()->getName() );
    Node * from = getNodeByName( e->getFromNode()->getName() );
    Node * to = getNodeByName( e->getToNode()->getName() );
    collectedNode.clear();
    if( isCycle( from, to ) ) return false;
    addEdge( getNodeByName( e->getFromNode()->getName() ), getNodeByName( e->getToNode()->getName() ), e->getWeight() );
    return true;
}
//..........................................................................................
Edge * Graph::findAndAddMinEdge( ) {
    double minW = INT_MAX;
    Edge * edge = nullptr;
    for( auto e : edges ) {
        if( e->getWeight() >= minW ) continue;
        minW = e->getWeight();
        edge = e;
    }
    return edge;
}
//..........................................................................................
Node * Graph::findMinNode() {
    int minN = INT_MAX;
    Node * node = nullptr;
    for( auto n : nodes ) {
        if( n->getFromEdge().size() and n->getToEdge().size() ) continue;
        if( n->getFromEdge().size() > 1 or n->getToEdge().size() > 1 ) continue;
        if( n->getName() >= minN ) continue;
        minN = n->getName();
        node = n;
    }
    return node;
}
//..........................................................................................
void Graph::findSpanningTree( Graph & span ) {
    while( span.edges.size() != nodes.size() - 1 ) {
        Edge * edge = findAndAddMinEdge();
        if( span.addUniqEdge( edge ) ) removeEdge(edge);
    }
}
//..........................................................................................

Node * Graph::getNodeByName( int name ) const {
    if( nodesMap.find( name ) == nodesMap.end() ) return nullptr;
    return nodesMap.at( name );
}
//..........................................................................................
void Graph::findPrufer() {
    std::vector<int>code;
    while( nodes.size() ) {
        Node * n = findMinNode();
        if( n->getFromEdge().size() ) code.push_back( n->getFromEdge()[ 0 ]->getFromNode()->getName() );
        else if( n->getToEdge().size() ) code.push_back( n->getToEdge()[ 0 ]->getToNode()->getName() );
        removeNode( n );
    }
    for( auto c : code ) {
        std::cout << c << " ";
    }
}
//..........................................................................................

void Graph::removeEdge( Edge * e ) {
    for( auto n : nodes ) {
        n->removeEdge( e );
    }
    for( size_t i = 0; i < edges.size(); i++ ) {
        if( edges[ i ] == e ) {
            delete e;
            edges.erase( edges.begin() + i );
            return;
        }
    }
}
//..........................................................................................
void Graph::removeNode( Node * n ) {
    for( auto e : n->getFromEdge() ) removeEdge( e );
    for( auto e : n->getToEdge() ) removeEdge( e );
    for( size_t i = 0; i < nodes.size(); i++ ) {
        if( nodes[ i ] == n ) {
            delete n;
            nodes.erase( nodes.begin() + i );
            return;
        }
    }
}
//..........................................................................................
bool Graph::isCycle( Node * fr, Node * t ) {
    for( auto ed : fr->getFromEdge() ) {
        if( ed->getFromNode() == t )  return true;
        if( collectedNode.find(ed->getFromNode()->getName()) != collectedNode.end() )  continue;
        else {
            collectedNode.insert( fr->getName() );
            ( isCycle( ed->getFromNode(), t ) );
        }
    }
    for( auto ed : fr->getToEdge() ) {
        if( ed->getToNode() == t )  return true;
        if( collectedNode.find(ed->getToNode()->getName()) != collectedNode.end() )  continue;
        else {
            collectedNode.insert( fr->getName() );
            ( isCycle( ed->getToNode(), t ) );
        }
    }
    return false;
}
//..........................................................................................

void Graph::print( std::ostream & os ) {
   /* for( auto n : nodes ) {
        if( n->isSource() ) printNode( n, os );
    }*/

    /*for( auto n : nodes ) {
        std::cout << "x" << n->getName() << std::endl;
    }*/
    for( auto e : edges ) {
        std::cout << "x" << e->getFromNode()->getName() << " x" << e->getToNode()->getName() << " " << e->getWeight() << std::endl;
    }
}

//..........................................................................................
