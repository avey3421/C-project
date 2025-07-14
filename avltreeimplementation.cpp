#include <iostream>
#include "avltree.h"
#include <fstream>

using namespace std;

int AVLtree::findmin() //επιστρέφει την ελάχιστη τιμή του δέντρου
{
    int min;
    NodeAVL *current=root;
    if (current!=nullptr)
    {
        while (current->getLeftChild()!=nullptr) //επαναληπτικά διατρέχει την αριστερή πλευρά του δέντρου μεχρι
        {                                        //να φτάσει σε κόμβο που δεν έχει αριστερό παιδί(ο ζητούμενος κόμβος) 
            current=current->getLeftChild();
        }
        min=current->getValue();
        return min;
    }
    return 0;
}

NodeAVL *AVLtree::search(int x) //αναζητά την τιμή x, διατρέχοντας το αριστερό παιδί του εκάστοτε κόμβου, αν η τιμή του κόμβου 
{                               //είναι μεγαλύτερη της x, η το δεξί παιδί αν η τιμή του κόμβου είναι μικρότερη της x
    bool flag=false;
    NodeAVL *current=root;
    if (current!=nullptr)
    {
        while (flag==false)
        {
            if (current->getValue()==x)
            {
                flag=true;
            }
            else if (current->getValue()<x)
            {
                current=current->getRightChild();
            }
            else
            {
                current=current->getLeftChild();
            }
            if (current==nullptr)
            {
                flag=true;
            }
        }
    }
    return current; //επιστρέφει τη διεύθυνδη του κόμβου με την τιμή x, και αν η τιμή x δεν εμφανίζεται στο δέντρο επιστρέφει κενό δείκτη
}

void AVLtree::rotate(NodeAVL *a, NodeAVL *b) //εκτελεί την απλή περιστροφή στους κόμβους του δέντρου, για μετατροπή μη AVL δέντρου σε AVL
{                                            //Ο κόμβος a βρίσκεται δεξιότερα (έχει μικρότερη τιμή) από τον b, ανεξάρτητα από το ποιός είναι ο γονιός ποιανού
    NodeAVL *c=nullptr, *temp3=nullptr;
    int da, db;
    da=(a->getDepth());
    db=(b->getDepth());
    if (da<db) //περίπτωση όπου ο a είναι γονιός του b (το βάθος του a είναι μικρότερο, όπου βάθος η "απόσταση" από τη ρίζα)  
    {
        temp3=(b->getLeftChild());
        c=temp3;
        temp3=nullptr;
        temp3=(a->getParent());
        b->setParent(temp3);
        if (temp3!=nullptr)
        {
            if ((temp3->getLeftChild())==a)
            {
                temp3->setLeftChild(b);
            }
            else
            {
                temp3->setRightChild(b);
            }
        }
        temp3=nullptr;
        b->setLeftChild(a);
        a->setParent(b);
        a->setRightChild(c);
        if (c!=nullptr)
        {
            c->setParent(a);
        }
        
        b->setDepth(da);
        if (da==0)
        {
            root=nullptr;
            root=b;
        }
    }
    else //περίπτωση όπου ο b είναι γονιός του a (το βάθος του b είναι μικρότερο, όπου βάθος η "απόσταση" από τη ρίζα)
    {
        temp3=(a->getRightChild());
        c=temp3;
        temp3=nullptr;
        temp3=(b->getParent());
        a->setParent(temp3);
        if (temp3!=nullptr)
        {
            if ((temp3->getLeftChild())==b)
            {
                temp3->setLeftChild(a);
            }
            else
            {
                temp3->setRightChild(a);
            }
        }
        temp3=nullptr;
        a->setRightChild(b);
        b->setParent(a);
        b->setLeftChild(c);
        if (c!=nullptr)
        {
            c->setParent(b);
        }
        a->setDepth(db);
        if (db==0)
        {
            root=nullptr;
            root=a;
        }
    }
}

void AVLtree::doubleRotate(NodeAVL *a, NodeAVL *z, NodeAVL *b) //μέθοδος που εκτελεί διπλή περιστροφή στους κόμβους του δέντρου
{                                                              //Ο κόμβος a βρίσκεται δεξιότερα (έχει μικρότερη τιμή) από τον z, ο οποίος βρίσκεται
    NodeAVL *c1=nullptr, *c2=nullptr, *temp10=nullptr;         // δεξιότερα από τον b, ανεξάρτητα από το ποιός είναι ο γονιός ποιανού
    int da, db;
    c1=(z->getLeftChild());
    c2=(z->getRightChild());
    da=(a->getDepth());
    db=(b->getDepth());
    if (da<db) //περίπτωση όπου ο a είναι γονιός του b (το βάθος του a είναι μικρότερο, όπου βάθος η "απόσταση" από τη ρίζα) και ο b γονιός του z
    {
        temp10=(a->getParent());
        z->setParent(temp10);
        if (temp10!=nullptr)
        {
            if (temp10->getLeftChild()==a)
            {
                temp10->setLeftChild(z);
            }
            else
            {
                temp10->setRightChild(z);
            }
        }
    }
    else //περίπτωση όπου ο b είναι γονιός του a (το βάθος του b είναι μικρότερο, όπου βάθος η "απόσταση" από τη ρίζα) και ο a γονιός του z
    {
        temp10=(b->getParent());
        z->setParent(temp10);
        if (temp10!=nullptr)
        {
            if (temp10->getLeftChild()==b)
            {
                temp10->setLeftChild(z);
            }
            else
            {
                temp10->setRightChild(z);
            }
        }
    }
    temp10=nullptr;
    z->setLeftChild(a);
    a->setParent(z);
    z->setRightChild(b);
    b->setParent(z);
    a->setRightChild(c1);
    if (c1!=nullptr)
    {
        c1->setParent(a);
    }
    b->setLeftChild(c2);
    if (c2!=nullptr)
    {
        c2->setParent(b);
    }
    if (da<db)
    {
        z->setDepth(da);
        if (da==0)
        {
            root=nullptr;
            root=z;
        }
    }
    else
    {
        z->setDepth(db);
        if (db==0)
        {
            root=nullptr;
            root=z;
        }
    }
}

int AVLtree::findSubtreeDepth(NodeAVL *a) //βρίσκει το βάθος/ύψος ενός υποδέντρου, αναδρομικά
{
    NodeAVL *temp2=nullptr;
    int d,sd1=0,sd2=0;
//cout<<(a->getValue())<<endl;
    if (a==nullptr)
    {
        d=-1;
    }
    else
    {
        if (a->getLeftChild()!=nullptr)
        {
            temp2=(a->getLeftChild());
            a=nullptr;
            sd1=findSubtreeDepth(temp2);
            a=(temp2->getParent());
            temp2=nullptr;
        }
        if (a->getRightChild()!=nullptr)
        {
            temp2=(a->getRightChild());
            a=nullptr;
            sd2=findSubtreeDepth(temp2);
            temp2=nullptr;
        }
        a=nullptr;
        if (sd1>sd2)
        {
            d=sd1;
        }
        else
        {
            d=sd2;
        }
    }
//cout<<"val: "<<a->getValue()<<endl;
//cout<<d<<", "<<sd1<<", "<<sd2<<endl;
    return ++d;
}

void AVLtree::insertNode(int v) //εισαγωγή νέου κόμβου με τιμή v
{
    treesize++;
    if (root==nullptr) //περίπτωση που το δέντρο είναι άδειο
    {
        root=new NodeAVL(v, nullptr);
    }
    else
    {
        NodeAVL *current=root, *vnode=nullptr, *temp=nullptr, *temp5=nullptr, *temp11=nullptr;
        int flag=0, dleft=0, dright=0;
        while (flag==0) //αναζήτηση κατάλληλης θέσης για τον κόμβο, ώστε το δέντρο να παραμείνει δυαδικό αναζήτησης
        {
            if (current->getValue()<v)
            {
                if (current->getRightChild()!=nullptr)
                {
                    temp=(current->getRightChild());
                    current=nullptr;
                    current=temp;
                }
                else
                {
                    flag=2;
                }
            }
            else
            {
                if (current->getLeftChild()!=nullptr)
                {
                    temp=(current->getLeftChild());
                    current=nullptr;
                    current=temp;
                }
                else
                {
                    flag=1;
                }
            }
        }
        vnode= new NodeAVL(v, current); //δημιουργία του νέου κόμβου
        if (flag==1)
        {
            current->setLeftChild(vnode);
        }
        else
        {
            current->setRightChild(vnode);
        }
//cout<<(current->getValue())<<endl;
        temp=(current->getParent());
        current=nullptr;
        current=temp;
        temp=nullptr;
//cout<<(current->getValue())<<endl;
//cout<<endl;
//tempprint(root);
//cout<<endl;
        while (current!=nullptr) //έλεγχοι για το αν παραμένει το δέντρο AVL. Σε περίπτωση που δέν είναι,γίνονται οι κατάλληλες περιστροφές
        {
            temp=(current->getLeftChild());
            dleft=findSubtreeDepth(temp);
            temp=nullptr;
//cout<<"dleft: "<<dleft<<endl;
            temp=(current->getRightChild());
            dright=findSubtreeDepth(temp);
            temp=nullptr;
//cout<<"dright: "<<dright<<endl;
            if (dleft-dright>1)
            {
                temp=(current->getLeftChild());
                temp5=current;
                if ((temp->getLeftChild())!=nullptr)
                {
                    rotate(temp, temp5);
                }
                else
                {
                    temp11=(temp->getRightChild());
                    doubleRotate(temp, temp11, temp5);
                    temp11=nullptr;
                }
                temp=nullptr;
                temp5=nullptr;
            }
            else if (dleft-dright<-1)
            {
                temp=(current->getRightChild());
                temp5=current;
                if ((temp->getRightChild())!=nullptr)
                {
                    rotate(temp5, temp);
                }
                else
                {
                    temp11=(temp->getLeftChild());
                    doubleRotate(temp5, temp11, temp);
                    temp11=nullptr;
                }
                temp=nullptr;
                temp5=nullptr;
            }
            temp=(current->getParent());
            current=nullptr;
            current=temp;
            temp=nullptr;
        }
    }
root->setDepth(0); //αναδρομικά ανανεώνονται οι τιμές "depth", των κόμβων, που τυχόν να μεταβλήθηκαν κατα τις περιστροφές
treedepth=findSubtreeDepth(root);
//cout<<endl;
//tempprint(root);
//cout<<endl;
}

void AVLtree::buildAVLTree(const char *filename) //μέθοδος για τη δημιουργία δέντρου, με είσοδο ένα πίνακα ακεραίων με τις τιμές εισαγωγής και τον αριθμό εισαγωγών
{
    fstream file;
    file.open(filename,ios::in);
    if (!file.is_open()) return;
    int data;
    while (file >> data) {
        insertNode(data);
    }
    file.close();
}

void AVLtree::deleteNode(int v) //διαγραφή κόμβου με τιμή v
{
    int dleft, dright;
    NodeAVL *n=nullptr, *current=nullptr, *temp6=nullptr, *temp7=nullptr, *temp8=nullptr;
    n=search(v); //αναζήτηση του κόμβου με την τιμή v
//cout<<(n->getValue());
    if (n!=nullptr)
    {
        temp6=(n->getLeftChild());
        temp7=(n->getRightChild());
        while ((temp6!=nullptr)&&(temp7!=nullptr)) //περιστροφές του κόμβου που θα αφεραιθεί, ώστε να έχει ένα ή κανένα κόμβο "παιδί" 
        {
            if (findSubtreeDepth(temp6)<findSubtreeDepth(temp7))
            {
                rotate (temp6, n);
            }
            else
            {
                rotate (n, temp7);
            }
            temp6=nullptr;
            temp7=nullptr;
            temp6=(n->getLeftChild());
            temp7=(n->getRightChild());
        }
        if (temp6==nullptr) //αλλάζω το παιδί του πατέρα του n και τον πατέρα του παιδιού του n, αν υπάρχει
        {
            current=temp7;
        }
        else
        {
            current=temp6;
        }
        temp6=nullptr;
        temp7=nullptr;
        temp6=(n->getParent());
        if (temp6!=nullptr)
        {
            if (temp6->getLeftChild()==n)
            {
                temp6->setLeftChild(current);
            }
            else
            {
                temp6->setRightChild(current);
            }
        }
        if (current!=nullptr)
        {
            current->setParent(temp6);
            if (temp6==nullptr)
            {
                root=current;
            }
        }
        else if (temp6==nullptr)
        {
            root=nullptr;
        }
        current=temp6;
        temp6=nullptr;
        if (root!=nullptr)
        {
            root->setDepth(0);
        }
        if (current!=nullptr)
        {
            temp6=(current->getLeftChild());
            temp7=(current->getRightChild());
            if ((temp6==nullptr)&&(temp7==nullptr))
            {
                temp8=(current->getParent());
                current=temp8;
                temp8=nullptr;
            }
            while (current!=nullptr) //έλεγχοι για το αν παραμένει το δέντρο AVL. Σε περίπτωση που δέν είναι,γίνονται οι κατάλληλες περιστροφές
            {
                dleft=findSubtreeDepth(temp6);
                dright=findSubtreeDepth(temp7);
                if (dleft-dright>1)
                {
                    if ((temp6->getLeftChild())!=nullptr)
                    {
                        rotate(temp6, current);
                    }
                    else
                    {
                        temp8=(temp6->getRightChild());
                        doubleRotate(temp6, temp8, current);
                        temp8=nullptr;
                    }
                }
                else if (dleft-dright<-1)
                {
                    if ((temp7->getRightChild())!=nullptr)
                    {
                        rotate(current, temp7);
                    }
                    else
                    {
                        temp8=(temp7->getLeftChild());
                        doubleRotate(current, temp8, temp7);
                        temp8=nullptr;
                    }
                }
                temp8=(current->getParent());
                current=temp8;
                temp8=nullptr;
            }
            temp6=nullptr;
            temp7=nullptr;
        }
        if (root!=nullptr)
        {
            root->setDepth(0); //αναδρομικά ανανεώνονται οι τιμές "depth", των κόμβων, που τυχόν να μεταβλήθηκαν κατα τις περιστροφές
        }
        treedepth=findSubtreeDepth(root);
        treesize--;
        n->setParent(nullptr); //διαγραφή του κόμβου από τη μνήμη, με κενούς όλους τους δείκτες του, για να αποφευχθεί αναδρομικά η διαγραφή τους
        n->setRightChild(nullptr); //(βλέπε destructor των κόμβων (NodeAVL))
        n->setLeftChild(nullptr);
        delete n;
//cout<<endl;
//tempprint(root);
//cout<<endl;
    }
}





void AVLtree::tempprint(NodeAVL *a) //προσωρινή μέθοδος εκτύπωσης του δέντρου, για διεξαγωγή ελέγχων
{
    if (a!=nullptr)
    {
        cout<<(a->getValue());
        if (a->getLeftChild()!=nullptr)
        {
            cout<<"<";
        }
        if (a->getRightChild()!=nullptr)
        {
            cout<<">";
        }
        if ((a->getLeftChild()==nullptr)&&(a->getRightChild()==nullptr))
        {
            cout<<"|";
        }
        cout<<" ";
        if (a->getLeftChild()!=nullptr)
        {
            tempprint(a->getLeftChild());
        }
        if (a->getRightChild()!=nullptr)
        {
            tempprint(a->getRightChild());
        }
    }
    else
    {
        cout<<"NULL";
    }
    
}












