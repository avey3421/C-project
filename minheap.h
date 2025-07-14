#ifndef MINHEAP_H
#define MINHEAP_H

class Minheap
{
    private:
        int H[1000]; //Ο πίνακας που υλοποιεί τη minheap
        int size=0; //Το μέγεθος του πίνακα - αριθμός στοιχείων
        
    public:
        Minheap()=default; //ένας default constructor
        int getSize() {return size;} //getter για το μέγεθος
        void setSize(int s) {size=s;} //setter για το μέγεθος
        int findMin() {return H[0];} //εύρεση ελάχιστου στοιχείου
        void insertMinheap(int n); //εισαγωγή στοιχείου n
        void deleteMin(); //διαγραφή ελαχίστου
        void swap(int n, int m); //αντιμετάθεση δύο κόμβων
        int getElement(int pos) {return H[pos];} //getter για την τιμή του πίνακα στη θέση pos 
        void buildMinheap(const char *filename); //Η μέθοδος που κατασκευάζει τη minheap
        
};

#endif