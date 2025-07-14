#include "minheap.h"
#include <fstream>
using namespace std;
void Minheap::swap(int c, int p) //αντιμετάθεση δύο κόμβων
{
    int temp;
    temp=H[c];
    H[c]=H[p];
    H[p]=temp;
}

void Minheap::insertMinheap(int n) //εισαγωγή στοιχείου n
{
    if (size==0) //περίπτωση άδειας minheap
    {
        H[0]=n;
        size=1;
    }
    else
    {
        int c,p;
        H[size]=n; //εισαγωγή στη βάση της minheap
        c=size;
        p=(c-1)/2;
        size++;
        while (H[c]<H[p]) //έλεγχος για αντιμεταθέσεις για σωστή τοποθέτηση
        {
            swap(c, p);
            c=p;
            p=(c-1)/2;
        }
    }
}

void Minheap::deleteMin() //διαγραφή ελαχίστου
{
    bool flag=false;
    int c,p;
    H[0]=H[size-1];
    size--;
    if (size>1)
    {
        p=0;
        if (H[2*p+1]<H[2*p+2])
        {
            c=2*p+1;
        }
        else
        {
            c=2*p+2;
        }
        if (c>=size)
        {
            flag=true;
        }
        if (flag==false)
        {
            while ((H[c]<H[p])&&(flag==false)) //επαναλαμβανόμενες αντιμεταθέσεις όποτε χρειάζονται
            {
                swap(c, p);
                p=c;
                if (2*p+1<2*p+2)
                {
                    c=2*p+1;
                }
                else
                {
                    c=2*p+2;
                }
                if (c>=size)
                {
                    flag=true;
                }
            }
        }
    }
}

void Minheap::buildMinheap(const char *filename) //Η μέθοδος που κατασκευάζει τη minheap
{
    fstream file;
    file.open(filename, ios::in);
    if (!file.is_open()) return;
    int data;
    while (file >> data) {
        insertMinheap(data);
    }
    file.close();
}