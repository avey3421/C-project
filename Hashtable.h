#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <fstream>
using namespace std;

class Hashtable {
private:
    int size = 0;
    int capacity = 1000;
    int **table=new int*[capacity]();
public:
    Hashtable()=default;
    ~Hashtable(){delete [] table;}
    Hashtable(int capacity) {
        this->capacity=capacity;
        table = new int*[capacity];
    }
    void insert(int value);
    bool search(int number);
    int getsize(){
        return size;
    }
    void build_hashtable(const char *filename);

};

#endif //HASHTABLE_H
