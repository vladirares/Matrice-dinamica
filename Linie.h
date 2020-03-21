#include"Element.h"
using namespace std;

class Linie{
    Element *prim, *ultim;      //pointeri catre primul si ultimul element din linie
    Linie *next, *prev;         //pointeri catre linia urmatoare respectiv precedenta
    unsigned length;
public:
    Linie();                    //constructor fara param.
    Linie(const Linie&);        //constructor de copiere
    void pushRight(int);
    void pushLeft(int);
    int popRight();
    int popLeft();
    void removeAt(int);
    int getLength();
    void print();
    void setNext(Linie*);
    void setPrev(Linie*);
    Element* getPrim();
    Element* getUltim();
    Linie* getNext();
    Linie* getPrev();

    Element& operator[](int);
    friend ostream& operator<<(ostream& out,const Linie& line); //supraincarcarea operatorului <<
    //~Linie();
};
