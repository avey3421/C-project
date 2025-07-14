//
// Created by wwwji on 2025-06-27.
//

#ifndef NODE_H
#define NODE_H
#define num_of_edges 100

#include "Edge.h"


class Node {
private:
  int colour=0;
  int data=0;
  int id=0;
  int num_edge=0;
  Edge *edges[num_of_edges]={nullptr};
public:
  Node()=default;
  Node(int id){this->id=id;}
  ~Node() {
    for (int i = 0; i < num_of_edges; i++)
      delete edges[i];
  }
  void insertEdge(Edge *edge) {
    edges[num_edge++] = edge;
  }
  void setData(int data) {this->data=data;}

  void deleteEdge(Edge *edge) {
    for (int i = 0; i < num_edge; i++) {
      if (edges[i] == edge) {
        int j;
        for ( j = i+1; edges[j]!=nullptr; j++) {
          edges[j-1] = edges[j];
        }
        edges[j-1]=nullptr;   // since we do a resize, the last element will be nullptr (shift to the left of all the edges)
        num_edge--;
        return;
      }
    }
  }
  int getData() {
    return data;
  }
  int getEdges() {
    return num_edge;
  }
  int getId() {
    return id;
  }
  int getNumEdge() {
    return num_edge;
  }
  int getColour() {return colour;}
  void setColour(int colour) {this->colour=colour;}
  Edge **getNeighbours(int *i) {
       *i = num_edge;
       Edge **temp = new Edge*[num_edge];
       for (int i = 0; i < num_edge; i++) {
         temp[i] = edges[i];
       }
       return temp;
  }
  void getInfo() {
    cout <<"id is "+to_string(id)+ " and connects to the nodes with ids:\n";
    for (int i=0; i<num_edge; i++) {
      cout << edges[i]->getEndpoint()->getId() << " with weight " <<  edges[i]->getWeight()<<endl;
    }
    cout << "and has this many edges: "<<num_edge<<endl;
  }
};




#endif //NODE_H
