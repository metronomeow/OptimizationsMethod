#pragma once
#include <vector>
#include <ostream>

class Edge;
class Node;
std::ostream & operator << ( std::ostream & os, Node node );


class Node {
public:
    Node( int sym );
    void addFromEdge( Edge * from );
    void addToEdge( Edge * to );
    void removeEdge( Edge * e );

    int getName() const { return name; }

    const std::vector < Edge *> & getFromEdge() const { return fromEdge; }
    const std::vector < Edge *> & getToEdge() const { return toEdge; }

private:
    int name;

    std::vector < Edge *> fromEdge;
    std::vector < Edge *> toEdge;

    friend std::ostream & operator << ( std::ostream & os, Node node );
};
