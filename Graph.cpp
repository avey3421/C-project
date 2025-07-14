#include "Graph.h"
#include <fstream>
#include <climits>
#include <iostream>
using namespace std;
void Graph::insertEdge(int id1, int id2, int weight) {
	int x1=0,y1=0;
	Node *x=new Node(id1);   // i will create 2 dummy nodes here, if i find that they already exist ill just copy them to the pointer
	Node *y=new Node(id2);    // when the function will finish, these pointers will be deleted but the new nodes that are created will still exist
	// if one of these 2 dummy nodes is actually a new node i will just add them to the nodes list like im doing later
	for (int i = 0; i < numNodes ; i++) {               // ill check if at least one of the nodes does NOT exist in the graph
		if(x->getId() == nodes[i]->getId()) {
			x1=1;
			x=nodes[i];                  // x is a new node i create in main so it doesnt have all the data that the actual one has, will use this later in connected()
			if (connected(nodes[i],y->getId())) return;
			cout << x->getEdges()<<endl;
		} else if (y->getId() == nodes[i]->getId()) {
			y1=1;
			y=nodes[i];
			if (connected(nodes[i],x->getId())) return;
            cout << y->getEdges()<<endl;
		}
	}
	Edge *temp = new Edge(x,y,weight);
	Edge *temp2 = new Edge(y,x,weight);
	numEdges++;
	x->insertEdge(temp);
	y->insertEdge(temp2);
	if (x1==0||y1==0) {  // at least 1 of them doesnt exist
		if (x1==0) {   // if i didnt find them in the previous search theyre new nodes, save them in the nodes array since the pointers
			// will be deleted
			nodes[numNodes++]=x;
			cout << x->getEdges()<<endl;
		}
		if(y1==0) {
			nodes[numNodes++]=y;
			cout << x->getEdges()<<endl;
		}
	}
}

int Graph::computespanningtree() {
	int sum=0,neighbours=0,min = INT_MAX, min_pos=0;
	for (int i=0; i<numNodes; i++) {
		nodes[i]->setData(0);
	}
	Edge **edgelist = new Edge *[0];
	int edgelist_size=0;
	Edge **new_nodes = nodes[0]->getNeighbours(&neighbours);     // this is the first computation so i do it out of the loop
	nodes[0]->setData(1);          // code goes like:
	Edge *minedge=nullptr;        // get the minimum edge from all the nodes ive visited so far
	for (int i = 0; i<neighbours; i++) {   // if the minimum edge leads to a new node add it
		resize_array<Edge>(edgelist,edgelist_size,1);   // from that new node gather all of its edges and put them in the edgelist
		edgelist[edgelist_size-1]=new_nodes[i];
		if (new_nodes[i]->getWeight() < min) {
			minedge = new_nodes[i];
			min = new_nodes[i]->getWeight();
			min_pos = i;
		}
	}
	Edge *temporary = edgelist[edgelist_size-1];  // swap the edge with least weight with the last element in edgelist
	edgelist[edgelist_size-1]=edgelist[min_pos];  // effectively gets removed in the resize_array function call
	edgelist[min_pos] = temporary;
	Node *current=nullptr;
	bool not_done=true;
	while (not_done) {
		current = minedge->getEndpoint();
		sum+=min;
		current->setData(1);
		resize_array(edgelist,edgelist_size,-1);
		new_nodes = current->getNeighbours(&neighbours);
		min = INT_MAX;
		for (int i = 0; i < neighbours; i++) { //add the neighbours of current which is the new visited node
			if (new_nodes[i]->getEndpoint()->getData()==0) {// data == 0  => undiscovered
				resize_array(edgelist,edgelist_size,1);
				edgelist[edgelist_size-1]=new_nodes[i];
			}
		}
		not_done=false;  //check if we need to visit new nodes
		for (int i = 0; i<edgelist_size; i++) {
			if (edgelist[i]->getWeight() < min && edgelist[i]->getEndpoint()->getData()==0) {
				not_done=true;  // this is if the graph has more than 1 component, i only find the minimum tree of 1 component
				min = edgelist[i]->getWeight();  // so if we have done that, the code will never reach this block
				minedge = edgelist[i];
				min_pos = i;// if we find a new min swap it with the last one so it gets effectively deleted
			}    // when we call resize array with change == -1
		}
		Edge *temporary = edgelist[edgelist_size-1];  // swap minimum edge with the last element in edgelist
		edgelist[edgelist_size-1]=edgelist[min_pos];
		edgelist[min_pos] = temporary;
	}
	for (int i=0; i<numNodes; i++) {
		nodes[i]->setData(0);  // reset for future calls
	}
	return sum;
}

void Graph::getSize(int *nod, int *edg) {
	*nod=numNodes;
	*edg=numEdges;
}

int Graph::findconnectedcomponents() {
	int components = 0;
	for (int i = 0; i < numNodes; i++) {
		if (nodes[i]->getData() == 0) {
			dfs(nodes[i]);    // dfs will turn all of the nodes that it will visit to 1, so if i find another 0 that implies an unvisited
			components++;  // node, new dfs call will be called there and so on until we have scanned all of the array
		}
	}
	for (int i = 0; i < numNodes; i++) {
		nodes[i]->setData(0);  // set it to 0 for later uses
	}
	return components;
}
void Graph::dfs(Node *n) {
	if (n->getData()==1) {      // code i did for a dfs algorithm to set the data of all the visited nodes to be set for 1
		return;        // for the method find connected components
	}
	n->setData(1); // i visited it
	int neigh;
	Edge **neighbours = n->getNeighbours(&neigh);
	for (int i = 0; i<neigh; i++) {
		dfs(neighbours[i]->getEndpoint());
	}
}

int Graph::computeshortestpath(int src,int dest) {
	bool found1=false,found2=false;
	Node *destination_node=nullptr;
	for (int i = 0; i < numNodes; i++) {
		if (nodes[i]->getId() == src) {
			nodes[i]->setData(0);
			found1=true;
		} else nodes[i]->setData(INT_MAX); // set dist to inf
		if (nodes[i]->getId() == dest) {       // we need to find both of source and destination node in order for the function to work
			destination_node = nodes[i];
			found2=true;
		}
	}
	if (found1==false || found2 == false) {
		for (int i =0; i<numNodes; i++) {
			nodes[i]->setData(0);
			nodes[i]->setColour(0);  // set them to 0 for later use in other methods
		}
		return 0;
	}
	int neighbours;
	int position_of_min = 0;
	Node **nodeList = new Node*[0];
	int nodelist_size=0;
	for (int m = 0; m<numNodes; m++) {  //put all the nodes with their initial distances
		resize_array<Node>(nodeList,nodelist_size,1);
		nodeList[nodelist_size-1]=nodes[m];
	}
	while (destination_node->getColour()==0) {    // main loop, i will stop when i compute the shortest distance for destination_node
		Node *min = nullptr;
		int minimum_dist = INT_MAX;
		for (int i = 0; i<nodelist_size; i++) {  // find the minimum computed distance so far (will delete it later to find new distances)
			if (nodeList[i]->getData()<minimum_dist) {
				min = nodeList[i];    // min is the node with the least distance so far from the starting one
				minimum_dist = nodeList[i]->getData();
				position_of_min = i;
			}
		}
		Node *last_node_in_nodelist = nodeList[nodelist_size-1];    // replace with last element in the array so it gets removed in
		nodeList[nodelist_size-1]=nodeList[position_of_min];   // resize
		nodeList[position_of_min] = last_node_in_nodelist;
		min->setColour(1);   // declare we have computed its shortest path
		Edge **new_edges_arr = min->getNeighbours(&neighbours);
		resize_array<Node>(nodeList,nodelist_size,-1);
		for (int k = 0; k<neighbours; k++) {                               // relax neighbours! might find new shorter paths for them
			if(new_edges_arr[k]->getEndpoint()->getData() > new_edges_arr[k]->getWeight()+min->getData()) {
				new_edges_arr[k]->getEndpoint()->setData(new_edges_arr[k]->getWeight()+min->getData());  // relax the neighbours of the
			}   // node with the most recent least travel computed
		}
	} // go back to find new shortest node without the current one we computed (so we move forwards)
	int res = destination_node->getData();
	for (int i =0; i<numNodes; i++) {
		nodes[i]->setData(0);
		nodes[i]->setColour(0);  // set them to 0 for later use in other methods
	}
	return res;
}

void Graph::delete_graph_edge(int src, int dest) {
	for (int i = 0; i<numNodes; i++) {
		if (nodes[i]->getId() == src || nodes[i]->getId() == dest) {
			int target;
			if (nodes[i]->getId() == src) target = dest;   // if we found the source node, we need to see if it connects to the dest
			else target = src;  // else if we found the dest node, we need to see if it connects to the src node
			Edge *connecting_edge=new Edge(new Node(INT_MAX),new Node(INT_MAX),INT_MAX);// making a dummy edge
			Node *end_node=new Node(INT_MAX);  // making a dummy node
			if (connected(nodes[i],target,&end_node,&connecting_edge)) {  // the dummy edge, nodes will be called by reference so they return
				nodes[i]->deleteEdge(connecting_edge);  // the actual edge and node, then will be passed to the methods
				end_node->deleteEdge(connecting_edge);   // deleteEdge just shifts all the edges in the edge array of the node by 1
				delete connecting_edge;
				// from the spot the targetted edge is found, so we delete it here (because i call the function for both nodes)
			}
			numEdges--;
			return;
		}
	}
}
bool Graph::connected(Node *n1, int n2_id,Node **dest_node,Edge **edge) {
	int neighbours;
	Edge **neighbours_arr = n1->getNeighbours(&neighbours);       // get the neighbours of the n1 node
	for (int j = 0; j < neighbours; j++) {
		if (neighbours_arr[j]->getEndpoint()->getId() == n2_id) {
			if (dest_node != nullptr && edge != nullptr) {     // if ive passed values to dest_node nd edge then change them (call by reference)
				*dest_node = neighbours_arr[j]->getEndpoint();
				*edge=neighbours_arr[j];
			}
			return true;
		}
	}
	return false;
}
void Graph::build_graph(const char *filename) {
	ifstream file;
	file.open(filename,ios::in);
	if (!file.is_open()) {
		return;
	}
	int id1,id2,weight;
	while (file >> id1 >> id2 >> weight) {
		insertEdge(id1,id2,weight);
	}
	file.close();
}
