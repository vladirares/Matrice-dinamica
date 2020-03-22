#include"Linie.h"

Linie::Linie(){                     //initializare
    prim = ultim = NULL;
    next = prev = NULL;
    length = 0;
}

Linie::Linie(const Linie &line){        //constructor de copiere
    this->length = 0;
    this->next = line.next;
    this->prev = line.prev;
    this->prim = NULL;
    this->ultim = NULL;

    Element *aux = line.prim;               //element auxiliar folosit pentru a parcurge lista
    for(int i=0; i < line.length; i++){
        this->pushRight(aux->getInfo());    //introducem element cu element in noua linie (se
        if(aux->getNext())                  //creeaza elemente noi in memorie atunci cand se
            aux = aux->getNext();           //apeleaza pushRight())
    }


}

void Linie::pushRight(int value){                       //metoda folosita pentru introducerea
    if(prim == NULL){                                   //elementelor in dreapta liniei
        prim = ultim = new Element(value,NULL,NULL);    //verificam daca linia este goala
        length++;
    }else{
        Element* el = new Element(value,NULL,ultim);    //daca lista nu e goala
        ultim->setNext(el);                             //introducem elementul in dreapta
        el->setPrev(ultim);                             //si setam prev-ul lui la elementul
        ultim = el;                                     //anterior iar nextul lui la null
        length++;                                       //in final ii atribuim pointerul ultim
    }
}

void Linie::pushLeft(int value){                        //analog pushRight()
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

int Linie::popRight(){                                  //metoda folosita pentru a scoate elemente
    if(prim==NULL){                                     //verificam daca linia este goala iar daca
        throw runtime_error("Pop from empty Line");     //este aruncam exceptie
    }else if(prim == ultim){                            //verificam daca are un singur element
        Element* toDelete = prim;
        prim = ultim = NULL;
        delete toDelete;                                //apelam destructorul ~Element
        length--;
    }else{
        Element* toDelete = ultim;                      //daca linia are mai mult de un element
        ultim = ultim->getPrev();                       //avem un pointer catre ultimul element
        ultim->setNext(NULL);                           //setam pointerul ultim la penultimul el
        delete toDelete;                                //apelam destructorul pentru ultimul el
        length--;
    }
}

int Linie::popLeft(){                                   //analog popRight()
    if(prim==NULL){
        throw runtime_error("Pop from empty Line");
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
    if(prim==NULL || index >= this->getLength() || index < 0){  //verificam daca indexul este inafara liniei
        throw out_of_range ("Index out of bounds");             //iar daca este arunca exceptie
    }else if(index == 0){                                       //daca indexul este 0 putem apela popLeft()
        this->popLeft();
    }else if(index == this->getLength()-1){                     //analog popRight()
        this->popRight();
    }else if(prim == ultim){                                    //daca avem un singur element
        Element* toDelete = prim;
        prim = ultim = NULL;
        delete toDelete;
        length--;
    }else{
        Element* toDelete = prim;                               //avem un pointer catre un element pe care
        for(int i = 0; i < index; i++)                          //il folosim sa refacem legaturile intre
            toDelete = toDelete->getNext();                     //elemente si in final sa apelam destructorul
        toDelete->getPrev()->setNext(toDelete->getNext());
        toDelete->getNext()->setPrev(toDelete->getPrev());
        delete toDelete;
        length--;
    }
}

int Linie::getLength(){                     //metoda pentru returnarea lungimii
    return length;
}

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

Element& Linie::operator[](int index){                  //supraincarcarea operatorului []
if(index >= this->getLength()){
        throw out_of_range ("Index out of bounds");     //daca indexul este inafara liniei
    }else{                                              //aruncam exceptie out of range
        Element *aux = this->prim;
        for(int i=0;i<index;i++){                       //altfel parcurgem linia cu un pointer
            aux = aux->getNext();                       //caruia ii returnam valoarea din adresa
        }                                               //de memorie pe care o pointeaza
        return *aux;
    }
}


ostream& operator<<(ostream& out, const Linie& line){   //supraincarcarea operatorului <<
     Element *el = line.prim;                           //parcurgem linia cu ajutorul unui
    while(el){                                          //pointer si oferim fluxului de iesire
        out<<el->getInfo()<<" ";                        //informatia din element;
        el = el->getNext();
    }
}

Linie::~Linie(){
    for(int i = 0; i < length ; i++ ){                  //stergem fiecare element pornind din dreapta
        this->popLeft();
    }
}
