#include <iostream>
#include "Graph.h"
/*#include "Graph.cpp"
#include "Hashtable.cpp"
#include "maxheapimplementation.cpp"
#include "minheapimplementation.cpp"
#include "avltreeimplementation.cpp"
#include "nodeavlimplementation.cpp"
*/
#include "Hashtable.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <string.h>
#include "nodeavl.h"
#include "avltree.h"
#include "maxheap.h"
#include "minheap.h"
using namespace std;

int main() {
	fstream input_file;
	input_file.open("commands.txt", ios::in);
	if (!input_file.is_open()) {
		return -1;
	}
	Graph graph;
	Hashtable hashtable;
	Minheap minheap;
	Maxheap maxheap;
	AVLtree avltree;

	fstream output;
	output.open("output.txt", ios::out);
	if (!output.is_open()) {
		return -1;
	}
	char command[100];
	char data_struct[100];
	while(input_file>>command) {

		if(!strcmp(command,"BUILD")) {
			input_file>>data_struct;
			if(!strcmp(data_struct,"GRAPH")) {
				auto start = std::chrono::high_resolution_clock::now();
				char graph_name[100];
				input_file>>graph_name;
				graph.build_graph(graph_name);
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output <<"Graph build took "<< duration.count() << "ms\n";
			} else if (!strcmp(data_struct,"HASHTABLE")) {
				auto start = std::chrono::high_resolution_clock::now();
				char hashtable_name[100];
				input_file>>hashtable_name;
				hashtable.build_hashtable(hashtable_name);
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output <<"Hashtable build took "<< duration.count() << "ms\n";
			} else if (!strcmp(data_struct,"MINHEAP") || !strcmp(data_struct,"MAXHEAP")) {
				auto start = std::chrono::high_resolution_clock::now();
				char filename[100];
				input_file>>filename;
				const char *min_or_max;
				if (!strcmp(data_struct,"MINHEAP")) {
					min_or_max="Minheap build took: ";
					minheap.buildMinheap(filename);
				} else {
					min_or_max="Maxheap build took: ";
					maxheap.buildMaxheap(filename);
				}
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output <<min_or_max<< duration.count() << "ms\n";
			} else if (!strcmp(data_struct,"AVLTREE")) {
				auto start = std::chrono::high_resolution_clock::now();
				char avltree_name[100];
				input_file>>avltree_name;
				avltree.buildAVLTree(avltree_name);
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output <<"AVLTree build took "<< duration.count() << "ms\n";
			}
		} else if (!strcmp(command,"DELETE")) {
			input_file>>data_struct;
			if (!strcmp(data_struct,"GRAPH")) {
				auto start = std::chrono::high_resolution_clock::now();
				int id1,id2;
				input_file >> id1 >> id2;
				graph.delete_graph_edge(id1,id2);
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output <<"Deleting edge from graph took "<< duration.count() << "ms\n";
			} else if (!strcmp(data_struct,"AVLTREE")) {
				auto start = std::chrono::high_resolution_clock::now();
				int data;
				input_file >> data;
				avltree.deleteNode(data);
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output <<"deleting "<< data <<" from avltree took "<< duration.count() << "ms\n";
			}
		} else if (!strcmp(command,"GETSIZE")) {
			input_file>>data_struct;
			if (!strcmp(data_struct,"GRAPH")) {
				auto start = std::chrono::high_resolution_clock::now();
				int edg,nodes;
				graph.getSize(&nodes,&edg);
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output<<"Graph currently contains "<<nodes<<" nodes and "<<edg<<" edges"<<endl;
				output<<"time it took: "<<duration.count()<<" ms\n";
			}
			else if (!strcmp(data_struct,"HASHTABLE")) {
				auto start = std::chrono::high_resolution_clock::now();
				output <<"Hashtable currently contains "<< hashtable.getsize() <<" elements"<<endl;
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output << "time it took:"<<duration.count()<<"ms\n";
			} else if (!strcmp(data_struct,"MINHEAP")) {
				auto start = std::chrono::high_resolution_clock::now();
				output << "Minheap currently contains "<<minheap.getSize()<<" elements"<<endl;
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output << "time it took:"<<duration.count()<<"ms\n";
			} else if (!strcmp(data_struct,"MAXHEAP")) {
				auto start = std::chrono::high_resolution_clock::now();
				output << "Maxheap currently contains "<<maxheap.getSize()<<" elements"<<endl;
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output << "time it took:"<<duration.count()<<"ms\n";
			} else if (!strcmp(data_struct,"AVLTREE")) {
				auto start = std::chrono::high_resolution_clock::now();
				output << "AVLtree currently contains "<<avltree.getTreesize()<<" elements"<<endl;
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output << "time it took:"<<duration.count()<<"ms\n";
			}
		} else if (!strcmp(command,"SEARCH")) {
			input_file>>data_struct;
			if (!strcmp(data_struct,"HASHTABLE")) {
				auto start = std::chrono::high_resolution_clock::now();
				int number;
				input_file>>number;
				bool found = hashtable.search(number);
				if (found) output << "SUCCESS"<<endl;
				else output << "FAILURE"<<endl;
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output << "Searching "<<number<< " in hashtable took "<<duration.count()<<"ms\n";
			} else if (!strcmp(data_struct,"AVLTREE")) {
				auto start = std::chrono::high_resolution_clock::now();
				int number;
				input_file>>number;
				bool found = avltree.search(number);
				if (found) output << "SUCCESS"<<endl;
				else output << "FAILURE"<<endl;
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output << "Time it took to search "<<number<<" in avltree: "<<duration.count()<<"ms\n";
			}
		} else if (!strcmp(command,"FINDCONNECTEDCOMPONENTS")) {
			input_file>>data_struct;
			if (!strcmp(data_struct,"GRAPH")) {
				auto start = std::chrono::high_resolution_clock::now();
				output <<"Graph currently has: "<<graph.findconnectedcomponents()<<" components"<<endl;
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output << "time it took "<<duration.count()<<" ms\n";
			}
		} else if (!strcmp(command,"DELETEMIN") ||!strcmp(command,"DELETEMAX")) {
			input_file>>data_struct;
			const char *data_str;
			auto start = std::chrono::high_resolution_clock::now();
			if (!strcmp(data_struct,"MINHEAP")) {
				data_str="Time to delete min from minheap took: ";
				minheap.deleteMin();
			} else {
				maxheap.deleteMax();
				data_str = "Time to delete max from maxheap took: ";
			}
			auto end = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
			output << data_str<<duration.count()<<"ms\n";
		} else if (!strcmp(command,"INSERT")) {
			input_file>>data_struct;
			if (!strcmp(data_struct,"GRAPH")) {
				int id1,id2,weight;
				auto start = std::chrono::high_resolution_clock::now();
				input_file >>id1 >>id2>>weight;
				graph.insertEdge(id1,id2,weight);
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output << "Time it took to insert edge in graph took: "<<duration.count()<<"ms\n";
			} else {
				auto start = std::chrono::high_resolution_clock::now();
				int data;
				input_file>>data;
				if (!strcmp(data_struct,"HASHTABLE")) hashtable.insert(data);
				else if (!strcmp(data_struct,"MINHEAP")) minheap.insertMinheap(data);
				else if (!strcmp(data_struct,"MAXHEAP")) maxheap.insertMaxheap(data);
				else if (!strcmp(data_struct,"AVLTREE")) avltree.insertNode(data);
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output << "Time it took to insert element took "<< duration.count()<<"ms\n";
			}
		} else if (!strcmp(command,"COMPUTESPANNINGTREE")) {
			input_file>>data_struct;
			if (!strcmp(data_struct,"GRAPH")) {
				auto start = std::chrono::high_resolution_clock::now();
				output << "Minimum Spanning Tree cost is: "<<graph.computespanningtree()<<endl;
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output << "Time it took "<<duration.count()<<" ms\n";
			}
		} else if (!strcmp(command,"FINDMIN")) {
			input_file>>data_struct;
			if (!strcmp(data_struct,"MINHEAP")) {
				auto start = std::chrono::high_resolution_clock::now();
				output << "minimum element in minheap is: "<<minheap.findMin()<<endl;
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output << "Time it took "<<duration.count()<<" ms\n";
			} else if (!strcmp(data_struct,"AVLTREE")) {
				auto start = std::chrono::high_resolution_clock::now();
				output << "Minimum element in AVL tree is "<<avltree.findmin()<<endl;
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output << "Time it took "<<duration.count()<<" ms\n";
			}
		} else if (!strcmp(command,"FINDMAX")) {
			input_file>>data_struct;
			if (!strcmp(data_struct,"MAXHEAP")) {
				auto start = std::chrono::high_resolution_clock::now();
				output << "maximum element in maxheap is: "<<maxheap.findMax()<<endl;
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output << "Time it took "<<duration.count()<<" ms\n";
			}
		} else if (!strcmp(command,"COMPUTESHORTESTPATH")) {
			input_file>>data_struct;
			if (!strcmp(data_struct,"GRAPH")) {
				int starting_node,finishing_node;
				input_file>>starting_node>>finishing_node;
				auto start = std::chrono::high_resolution_clock::now();
				output << "Shortest path from "<<starting_node<<" to "<<finishing_node<<" is "<<graph.computeshortestpath(starting_node,finishing_node)<<endl;
				auto end = std::chrono::high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
				output << "Time it took "<<duration.count()<<" ms\n";
			}
		}
	}
	output.close();


	return 0;
}
