# C-project
My project in data structures with my classmate partner, I coordinated the code part
//
My code is the files that code:
Node (for graph)
Edge (for Node)
Graph
Hashtable
Template Minheap

Everything else is done by my partner 

To use this project, in the commands.txt file you can write one of the following instructions per line
BUILD MINHEAP minheap.txt
BUILD MAXHEAP maxheap.txt
BUILD AVLTREE avltree.txt
BUILD GRAPH graph.txt
BUILD HASHTABLE hashtable.txt
GETSIZE MINHEAP (same for MAXHEAP, AVLTREE, GRAPH, HASHTABLE)
FINDMIN MINHEAP // finds and returns the minimum element in the minheap
FINDMAX MAXHEAP // finds and returns the max element in the maxheap
FINDMIN AVLTREE // finds and returns the minimum element from the AVL tree
SEARCH AVLTREE number // returns SUCCESS if the number element exists in the AVL tree, else FAILURE
SEARCH HASHTABLE number // returns SUCCESS if the number element exists in the hashtable, else FAILURE
COMPUTESHORTESTPATH GRAPH number1 number2 // computes the shortest path between the node with number1 and node number2 in the graph
COMPUTESPANNINGTREE GRAPH // computes the cost of the spanning tree of the current built graph
FINDCONNECTEDCOMPONENTS GRAPH // returns the number of the components that make up the current graph
INSERT MAXHEAP number (same for MAXHEAP, AVLTREE, HASHTABLE) // inserts number into the desired data structure
INSERT GRAPH number1 number 2 weight // inserts the node with number <number1> and <number2> in the graph and their connecting edge with weight <weight>
DELETEMIN MINHEAP
DELETEMAX MAXHEAP
DELETE GRAPH number1 number2 // deletes both nodes with number <number1> and <number2> respectively from the graph and their connecting edge


a new file, output.txt will be generated giving the results of the functions described above and their respective running time in microseconds
