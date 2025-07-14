#ifndef MAXHEAP_H
#define MAXHEAP_H

class Maxheap
{
    private:
        int H[1000]; //Ο πίνακας που υλοποιεί τη maxheap
        int size=0; //Το μέγεθος του πίνακα - αριθμός στοιχείων
        
    public:
        Maxheap()=default; //ένας default constructor
        int getSize() {return size;} //getter για το μέγεθος
        void setSize(int s) {size=s;} //setter για το μέγεθος
        int findMax() {return H[0];} //εύρεση μέγιστου στοιχείου
        void insertMaxheap(int n); //εισαγωγή στοιχείου n
        void deleteMax(); //διαγραφή μεγίστου
        void swap(int n, int m); //αντιμετάθεση δύο κόμβων
        int getElement(int pos) {return H[pos];} //getter για την τιμή του πίνακα στη θέση pos
        void buildMaxheap(const char *filename); //Η μέθοδος που κατασκευάζει τη maxheap
        
};

#endif