#ifndef GRAPH_H
#define GRAPH_H
#include "Edge.h"
#include <cmath>
#include "Node.h"
#define MAX_NODES 1000
#include <fstream>
#include <iostream>

using namespace std;
class Graph {
private:
    Node** nodes=new Node*[MAX_NODES];
    int numNodes=0,numEdges=0;
public:
    Graph() = default;
    ~Graph() {
        for (int i = 0; i < numNodes; i++) {
            delete nodes[i];     // delete each node pointer
        }
        delete[] nodes; // delete all of them afterwards
    }
    void insertEdge(int id1, int id2, int weight);
    void insertNode(Node *n) {
        nodes[numNodes++]=n;
    }
    int computespanningtree();
    void getInfo() {      // this method was used to test the code , nothing useful for main, just wanted to leave here if i revisit this project
        for (int i = 0; i < numNodes; i++) {
            cout <<"INFO FOR NODE: "<<i+1<<endl<<"---------"<<endl;
            nodes[i]->getInfo();
            cout << "--------------"<<endl;
        }
        int nod=0;
        int edg=0;
        getSize(&nod,&edg);
        cout<< "and has "<<edg<<" edges"<<endl;
        cout << "the lenght of the minimum spanning tree is : "<<computespanningtree()<<endl;
        int comp=findconnectedcomponents();
        cout << "number of connected components: "<<comp<<endl;
    }
    int getNumNodes() {
        return numNodes;
    }
    void getSize(int *nod, int *edg);
    int findconnectedcomponents();
    void dfs(Node *n);

    int computeshortestpath(int src,int dest);

    void delete_graph_edge(int src, int dest);

    bool connected(Node *n1, int n2_id,Node **dest_node=nullptr,Edge **edge=nullptr);

    template <class X>
    void resize_array(X **&array, int &size,int change) {
        X **temp = new X*[size+change]();
        int target = change == 1?size:size-1;  // if change is -1, the element i want to delete is at the end of the array
        for (int i = 0; i < target; i++) {  // so just make a new array with size-1 elements
            temp[i] = array[i];
        }
        for (int i = 0; i < size; i++) {
            array[i] = nullptr;
        }
        delete []array;
        size+=change;
        array = temp;
    }

    void build_graph(const char *filename);

};


#endif //GRAPH_H
