#include <iostream>
#include "nodeavl.h"

using namespace std;

NodeAVL::NodeAVL(int v, NodeAVL *p) //constructor της κλάσης, που δέχεται την τιμή και τη διεύθυνση του κόμβου "γονέα" του νέου κόμβου
{
    if (p==nullptr)
    {
        depth=0;
    }
    else
    {
        int temp = p->getDepth();
        depth=temp++;
    }
    value=v;
    parent=p;
    leftCh=nullptr;
    rightCh=nullptr;
}

NodeAVL::~NodeAVL() //destructor της κλάσης, που διαγράφει και τους κόμβους "παιδιά", για διαγραφή ολόκληρου του υποδέντρου
{
    delete rightCh;
    delete leftCh;
//cout<<"destructor"<<endl;
}

void NodeAVL::setDepth(int d) //setter του "βάθους", που αναδρομικά ανανεώνει το "βάθος" ολόκληρου του υποδέντρου
{
    depth=d;
//cout<<"a";
    if (leftCh!=nullptr)
    {
        leftCh->setDepth(d+1);
    }
    if (rightCh!=nullptr)
    {
        rightCh->setDepth(d+1);
    }
}