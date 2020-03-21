#include"Linie.h"

Linie::Linie(){
    prim = ultim = NULL;
    next = prev = NULL;
    length = 0;
}

Linie::Linie(const Linie &line){
    //this->length = line.length;
    this->length = 0;
    this->next = line.next;
    this->prev = line.prev;


    this->prim = NULL;
    this->ultim = NULL;

    /*this->prim = line.prim;
    this->ultim = line.ultim;*/

    Element *aux = line.prim;
    for(int i=0; i < line.length; i++){
        this->pushRight(aux->getInfo());
        if(aux->getNext())
            aux = aux->getNext();
    }


}

void Linie::pushRight(int value){
    if(prim == NULL){
        prim = ultim = new Element(value,NULL,NULL);
        length++;
    }else{
        Element* el = new Element(value,NULL,ultim);
        ultim->setNext(el);
        el->setPrev(ultim);
        ultim = el;
        length++;
    }
}

void Linie::pushLeft(int value){
    if(prim == NULL){
        prim = ultim = new Element(value,NULL,NULL);
        length++;
    }else{
        Element* el = new Element(value,prim,NULL);
        prim->setPrev(el);
        el->setNext(prim);
        prim = el;
        length++;
    }
}

int Linie::popRight(){
    if(prim==NULL){
        //arunca exceptie
    }else if(prim == ultim){
        Element* toDelete = prim;
        prim = ultim = NULL;
        delete toDelete;
        length--;
    }else{
        Element* toDelete = ultim;
        ultim = ultim->getPrev();
        ultim->setNext(NULL);
        delete toDelete;
        length--;
    }
}

int Linie::popLeft(){
    if(prim==NULL){
        //arunca exceptie
    }else if(prim == ultim){
        Element* toDelete = prim;
        prim = ultim = NULL;
        delete toDelete;
        length--;
    }else{
        Element* toDelete = prim;
        prim = prim->getNext();
        prim->setPrev(NULL);
        delete toDelete;
        length--;
    }
}

void Linie::removeAt(int index){
    if(prim==NULL || index >= this->getLength() || index < 0){
        //arunca exceptie
    }else if(index == 0){
        this->popLeft();
    }else if(index == this->getLength()-1){
        this->popRight();
    }else if(prim == ultim){
        Element* toDelete = prim;
        prim = ultim = NULL;
        delete toDelete;
        length--;
    }else{
        Element* toDelete = prim;
        for(int i = 0; i < index; i++)
            toDelete = toDelete->getNext();
        toDelete->getPrev()->setNext(toDelete->getNext());
        toDelete->getNext()->setPrev(toDelete->getPrev());
        delete toDelete;
        length--;
    }
}

int Linie::getLength(){
    return length;
}

/*
void Linie::print(){
    Element *el = prim;
    while(el){
        std::cout<<el->getInfo()<<" ";
        el = el->getNext();
    }
}
*/


void Linie::setNext(Linie* next){
    this->next = next;
}

void Linie::setPrev(Linie* prev){
    this->prev = prev;
}

Element* Linie::getPrim(){
    return prim;
}

Element* Linie::getUltim(){
    return ultim;
}

Linie* Linie::getNext(){
    return next;
}

Linie* Linie::getPrev(){
    return prev;
}

Element& Linie::operator[](int index){
if(index >= this->getLength()){
        //arunca exceptie de index out of range
    }else{
        Element *aux = this->prim;
        for(int i=0;i<index;i++){
            aux = aux->getNext();
        }
        return *aux;
    }
}


ostream& operator<<(ostream& out, const Linie& line){
     Element *el = line.prim;
    while(el){
        out<<el->getInfo()<<" ";
        el = el->getNext();
    }
}
