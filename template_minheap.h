//
// Created by wwwji on 2025-07-05.
//

#ifndef TEMPLATE_MINHEAP_H
#define TEMPLATE_MINHEAP_H

template <class T,class Compare>
class template_minheap
{
private:
    T *H[1000]={nullptr};
    int size=0;

public:
    template_minheap()=default;
    int getSize() {return size;}
    void setSize(int s) {size=s;}
    T *findMin() {return H[0];}
    void insertMinheap(T *n) {
        int c,p;
        if (size==0)
        {
            H[0]=n;
            size=1;
            c=0;
        }
        else
        {
            H[size]=n;
            c=size;
            p=(c-1)/2;
            size++;
            Compare cmp;
            while (cmp.compare(H[p],H[c]))
            {
                swap(c, p);
                c=p;
                p=(c-1)/2;
            }
        }
    }
    void deleteMin(){
        H[0]=H[size-1];
        H[size-1]=nullptr;
        size--;
        if (size==0) return;
        int parent_index=0,child_index_1=1,child_index_2=2;
        Compare cmp;
        T *compared;
        int index_of_compared;
        if (cmp.compare(H[child_index_1],H[child_index_2])) {  // if first child is greater than 2nd, grab 2nd
            compared = H[child_index_2];
            index_of_compared = child_index_2;
        }
        else {
            compared = H[child_index_1];
            index_of_compared = child_index_1;
        }
        while (cmp.compare(H[parent_index],compared)) {
            swap(parent_index, index_of_compared);
            parent_index=index_of_compared;
            child_index_1=2*parent_index+1;
            child_index_2=2*parent_index+2;
            if (cmp.compare(H[child_index_1],H[child_index_2])) {  // if first child is greater than 2nd, grab 2nd
                compared = H[child_index_2];
                index_of_compared = child_index_2;
            }
            else {
                compared = H[child_index_1];
                index_of_compared = child_index_1;
            }
        }
    }
    void swap(int n, int m){
        T* temp;
        temp=H[n];
        H[n]=H[m];
        H[m]=temp;
    }
    T *getElement(int pos) {return H[pos];}
};


#endif //TEMPLATE_MINHEAP_H
