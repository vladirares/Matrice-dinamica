#include"Element.h"

Element::Element(){         //initializare element
    info = 0;
    next = NULL;
    prev = NULL;
}

Element::Element(int info, Element* next, Element* prev){
    this->info = info;
    this->next = next;
    this->prev = prev;
}

Element::Element(const Element& el){        // in constructorul de copiere salvam doar informatia deoarece
    this->info = info;                      // elementul cand va fi introdus intr-o lista va avea atributele
    next = NULL;                            // next si prev initializate de metoda/constructorul care apeleaza
    prev = NULL;
}

void Element::setInfo(int info){
    this->info = info;
}

void Element::setNext(Element* next){
    this->next = next;
}

void Element::setPrev(Element* prev){
    this->prev = prev;
}

int Element::getInfo(){
    return info;
}

Element* Element::getNext(){
    return next;
}

Element* Element::getPrev(){
    return prev;
}


