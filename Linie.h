#include"Element.h"
using namespace std;

class Linie{
    Element *prim, *ultim;
    Linie *next, *prev;
    unsigned length;
public:
    Linie();
    Linie(const Linie&);
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
    friend ostream& operator<<(ostream& out,const Linie& line);
    //~Linie();
};
