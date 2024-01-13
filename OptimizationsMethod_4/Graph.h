#pragma once
#include <vector>
#include <map>
#include <ostream>

class Node;
class Edge;
class Graph {
public:
    ~Graph();
    bool addNode( int sym );
    bool addEdge( Node * fromNode, Node * toNode, double );
    bool addUniqEdge( Edge * e );
    Edge  * findAndAddMinEdge();
    void findSpanningTree( Graph & newGraph );
    Node * getNodeByName( int name ) const;
    Node * findMinNode();

    void findPrufer();

    void removeEdge( Edge * e );
    void removeNode( Node * n );
    bool isCycle( Node * fr, Node * t );

    void print( std::ostream & os );
    void clear();

private:
    std::map< int, Node * > nodesMap;
    std::vector<Node *> nodes;
    std::vector<Edge *> edges;
};