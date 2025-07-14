#ifndef NODEAVL_H
#define NODEAVL_H

class NodeAVL //η κλάση που υλοποιεί τους κόμβους που θα αποτελέσουν το δυαδικό δέντρο αναζήτησης AVL
{
    private:
        int depth; //το "βάθος" του κόμβου, που δείχνει την "απόσταση" από τον κόμβο "ρίζα"
        int value; //η τιμή του κόμβου
        NodeAVL *parent=nullptr; //διεύθυνση του κόμβου "γονέα"
        NodeAVL *leftCh=nullptr; //διεύθυνση του αριστερού κόμβου "παιδί"
        NodeAVL *rightCh=nullptr; //διεύθυνση του δεξιού κόμβου "παιδί"
        
    public:
        NodeAVL(int v, NodeAVL *p); //constructor της κλάσης, που δέχεται την τιμή και τη διεύθυνση του κόμβου "γονέα" του νέου κόμβου
        ~NodeAVL(); //destructor της κλάσης, που διαγράφει και τους κόμβους "παιδιά", για διαγραφή ολόκληρου του υποδέντρου
        void setDepth(int d); //setter του "βάθους", που αναδρομικά ανανεώνει το "βάθος" ολόκληρου του υποδέντρου
        int getDepth() {return depth;} //getter του "βάθους"
        void setValue(int v) {value=v;} //setter της τιμής
        int getValue() {return value;} //getter της τιμής
        void setParent(NodeAVL *n) {parent=n;} //setter του κόμβου "γονέα"
        NodeAVL *getParent() {return parent;} //getter του κόμβου "γονέα"
        void setLeftChild(NodeAVL *n) {leftCh=n;} //setter του αριστερού κόμβου "παιδί"
        NodeAVL *getLeftChild() {return leftCh;} //getter του αριστερού κόμβου "παιδί"
        void setRightChild(NodeAVL *n) {rightCh=n;} //setter του δεξιού κόμβου "παιδί"
        NodeAVL *getRightChild() {return rightCh;} //getter του δεξιού κόμβου "παιδί"
        
};

#endif