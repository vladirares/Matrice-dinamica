#include<iostream>

class Element{
    int info;
    Element* next;
    Element* prev;
public:
    Element();
    Element(int,Element*,Element*);
    Element(const Element&);
    void setInfo(int);
    void setNext(Element*);
    void setPrev(Element*);
    int getInfo();
    Element* getNext();
    Element* getPrev();

};
