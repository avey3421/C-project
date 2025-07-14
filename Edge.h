//
// Created by wwwji on 2025-06-27.
//

#ifndef EDGE_H
#define EDGE_H
#include <string>
#include <iostream>
using namespace std;
class Node;



class Edge {
private:
    int weight=0;
    Node *endpoint = nullptr;
    Node *start = nullptr;
public:
    Edge (Node *start, Node *endpoint, int lenght){
        weight = lenght;
        this->endpoint = endpoint;
        this->start = start;
    }
    void setEndpoint (Node *endpoint) {this->endpoint = endpoint;}
    void setStart (Node *start) {this->start = start;}
    void setWeight(int weight) {this->weight = weight;}
    Node *getEndpoint () {return endpoint;}
    Node *getStart () {return start;}
    int getWeight() {return weight;}
};



#endif //EDGE_H
