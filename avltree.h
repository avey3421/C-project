#ifndef AVLTREE_H
#define AVLTREE_H

#include "nodeavl.h"

class AVLtree //Η κλάση που υλοποιεί το δυαδικό δέντρο αναζήτησης AVL
{
    private:
        NodeAVL *root=nullptr; //Ο κόμβος "ρίζα" του δέντρου
        int treedepth; //Το βάθος/ύψος του δέντρου
        int treesize=0; //Αριθμός κόμβων
        
    public:
        AVLtree()=default; //Ένα default constructor
        ~AVLtree() {delete root;} //Destructor που καταστρέφει τη ρίζα και αναδρομικά όλους τους κόμβους του δέντρου (βλέπε destructor των κόμβων (του NodeAVL)) 
        int findmin(); //επιστρέφει την ελάχιστη τιμή του δέντρου
        int getTreesize() {return treesize;} //getter για το βάθος/ύψος του δέντρου
        void setTreesize(int s) {treesize=s;} //setter για το βάθος/ύψος του δέντρου
        NodeAVL *search(int x); ////αναζητά την τιμή x στο δέντρο
        void rotate(NodeAVL *a, NodeAVL *b); //εκτελεί την απλή περιστροφή στους κόμβους του δέντρου, για μετατροπή μη AVL δέντρου σε AVL
        void doubleRotate(NodeAVL *a, NodeAVL *z, NodeAVL *b); //μέθοδος που εκτελεί διπλή περιστροφή στους κόμβους του δέντρου
        int findSubtreeDepth(NodeAVL *a); //βρίσκει το βάθος/ύψος ενός υποδέντρου, αναδρομικά
        void insertNode(int v); //εισαγωγή νέου κόμβου με τιμή v
        void buildAVLTree(const char *filename); //μέθοδος για τη δημιουργία δέντρου, με είσοδο ένα πίνακα ακεραίων με τις τιμές εισαγωγής και τον αριθμό εισαγωγών
        void deleteNode(int v); //διαγραφή κόμβου με τιμή v
        
        void tempprint(NodeAVL *a); //προσωρινή μέθοδος εκτύπωσης του δέντρου, για διεξαγωγή ελέγχων
};

#endif