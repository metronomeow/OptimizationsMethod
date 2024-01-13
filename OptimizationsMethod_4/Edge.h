#pragma once

class Node;

class Edge {
public:
    Edge( Node * fromNode, Node * toNode, double weight ) : fromNode( fromNode ), toNode( toNode ), weight(weight) {}
    const Node * getFromNode() const { return fromNode; }
    const Node * getToNode() const { return toNode; }
    Node * getFromNode() { return fromNode; }
    Node * getToNode() { return toNode; }
    const double & getWeight() const { return weight; }
private:
    Node *fromNode;
    Node *toNode;
    double weight;
};

