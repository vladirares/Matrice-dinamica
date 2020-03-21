#include<iostream>

class Element{
    int info;
    Element* next;                      //pointer catre urmatorul element din linie
    Element* prev;                      //pointer catre elementul precedent din linie
public:
    Element();                          //constructor fara parametrii
    Element(int,Element*,Element*);     //constructor cu parametrii
    Element(const Element&);            //constructor de copiere
    void setInfo(int);
    void setNext(Element*);
    void setPrev(Element*);
    int getInfo();
    Element* getNext();
    Element* getPrev();

};
