#include "Hashtable.h"
#include <fstream>
using namespace std;
void Hashtable::insert(int value) {
	if (size == capacity) return;
	unsigned long current_key = (value * 2654435761)%capacity;
	if (table[current_key]==nullptr) {
		table[current_key] = new int;
		*table[current_key] = value;
		size++;
		return;
	}
	// current place is taken, probing now
	while (table[current_key]!=nullptr) { // while we encounter a taken place in the array...
		if (*table[current_key]==value) {
			return;  // if its already in the hashtable just return
		}               
		current_key = (current_key+1)%capacity;  // go to the new index
	}
	table[current_key] = new int;
	*table[current_key] = value;
	size++;
}

bool Hashtable::search(int number) {
	unsigned long current_key = number * 2654435761%capacity,first_key;
	first_key = current_key;
	do {
		if (table[current_key]!=nullptr) {  // if its not an empty seat in the array check if its same with our number
			if (*table[current_key] == number) {
				return true;
			}
		}
		current_key=(current_key+1)%capacity;
	} while (current_key != first_key);
	return false;
}

void Hashtable::build_hashtable(const char *filename) {
	ifstream file;
	file.open(filename,ios::in);
	if (!file.is_open()) {
		return;
	}
	int data;
	while (file >> data) {
		insert(data);
	}
	file.close();
}





