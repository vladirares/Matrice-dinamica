#include"Element.h"

Element::Element(){
    info = 0;
    next = NULL;
    prev = NULL;
}

Element::Element(int info, Element* next, Element* prev){
    this->info = info;
    this->next = next;
    this->prev = prev;
}

Element::Element(const Element& el){
    this->info = info;
    next = NULL;
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


