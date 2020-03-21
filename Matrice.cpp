#include<math.h>
#include"Matrice.h"
using namespace std;

Matrice::Matrice(int noLinii,int noCol,bool zeros){
    this->noLinii = noLinii;
    this->noCol = noCol;
    this->prim = NULL;
    this->ultim = NULL;

    if(zeros){                                  //daca zeros este true introduce linie cu linie
        for(int i = 0; i < noLinii; i++){       //cu ajutorul unui pointer zerouri in matrice
            Linie *line = new Linie();
            for(int j = 0; j < noCol; j++){
                line->pushRight(0);
            }
            this->insertLine(*line);
        }
    }
}

Matrice::Matrice(const Matrice& mat){
    this->noLinii = mat.noLinii;
    this->noCol = mat.noCol;
    this->prim = NULL;
    this->ultim = NULL;

    Linie *aux = mat.prim;                  //introducem linie cu linie in matricea noua
    for(int i=0; i < noLinii ; i++){        //cu ajutorul pointerului care parcurge
        this->insertLine(*aux);             //matricea care trebuie copiata
        aux = aux->getNext();
    }
}

void Matrice::insertLine(Linie linie){      //metoda privata
    Linie *pointerLine = new Linie(linie);  //facem un pointer catre o noua linie;
    if(prim == NULL){                       //daca matricea este goala (cum este in urma
        prim = ultim = pointerLine;         //constructorului cu parametrii cu zeros==false)
    }else{
        ultim->setNext(pointerLine);        //daca matricea nu este goala refacem legaturile
        pointerLine->setPrev(ultim);        //dintre linii. De observat ca insertLine() nu incrementeaza
        ultim = pointerLine;                //length , deoarece lungimea este setata de dinainte iar
    }                                       //aceasta nu poate fi apelata din afara (fiind privata)
}

int Matrice::getNoLinii(){
    return this->noLinii;
}

int Matrice::getNoCol(){
    return noCol;
}


float Matrice::getDeterminant(){
    float det = 0;
    Matrice *subMat = new Matrice(this->getNoLinii(),this->getNoCol(),true);
    if(this->getNoCol() != this->getNoLinii()){
        //aruncam exceptie
    }else if(this->getNoLinii() == 2){
        return( ((*this)[0][0].getInfo()*(*this)[1][1].getInfo()) - ((*this)[1][0].getInfo()*(*this)[0][1].getInfo()));
    }else{
        for(int x = 0; x < this->getNoLinii(); x++){
            int subi = 0;
            for(int i = 1; i < this->getNoLinii(); i++){
                int subj = 0;
                for(int j = 0 ; j < this->getNoLinii(); j++){
                    if(j == x)
                        continue;
                    ((*subMat)[subi][subj]).setInfo( (*this)[i][j].getInfo() );
                    subj++;
                }
                subi++;
            }
            Matrice *aux = new Matrice(*subMat);
            aux ->removeAt(aux->getNoLinii()-1,aux->getNoCol()-1);

            det = det + (pow(-1,x) * (*this)[0][x].getInfo() * aux->getDeterminant() );
        }
    }
    return det;

}

bool Matrice::isInvertible(){                   //daca determinantul este diferit de 0
    if(this->getDeterminant() == 0)             //matricea este inversabila
        return false;
    return true;
}


void Matrice::removeLineAt(int index){
    if(prim==NULL || index >= this->getNoLinii() || index < 0){ //verificam daca indexul este in interiorul liniei
        //arunca exceptie                                       //daca nu este aruncam exceptie de out of range
    }else if(index == 0){                                       //verificam daca este prima linie
        Linie *toDelete = prim;
        prim = prim->getNext();
        prim->setPrev(NULL);                                    //refacem legaturile dintre linii
        delete toDelete;                                        //apelam destructorul
        noLinii--;                                              //decrementam numarul de linii
    }else if(index == this->getNoLinii()-1){                    //verificam daca este ultima linie
        Linie *toDelete = ultim;
        ultim = ultim->getPrev();                               //refacem legaturile dintre linii
        ultim->setNext(NULL);
        delete toDelete;                                        //apelam destructorul
        noLinii--;                                              //decrementam numarul de linii
    }else if(prim == ultim){                                    //verificam daca linia contine doar un el
        Linie *toDelete = ultim;
        prim = ultim = NULL;
        delete toDelete;
        noLinii--;
    }else{
        Linie *toDelete = prim;                                 //cu ajutorul unui pointer catre prima linie
        for(int i = 0; i < index; i++){                         //parcurgem matricea
            toDelete = toDelete->getNext();
        }
        toDelete->getPrev()->setNext(toDelete->getNext());      //refacem legaturile
        toDelete->getNext()->setPrev(toDelete->getPrev());
        delete toDelete;                                        //apelam destructorul
        noLinii--;
    }
}

void Matrice::removeColAt(int index){
    if(prim==NULL || index >= this->getNoCol() || index < 0){   //verificam daca indexul este in matrice
        //arunca exceptie                                       //aruncam exceptie de out of range
    }else{
        for(int i=0; i < this->getNoLinii(); i++){              //parcurgem linie cu linie si ne folosim de
            (*this)[i].removeAt(index);                         //metoda removeAt() a Liniei.
        }
        noCol--;                                                //decrementam nr de coloane
    }
}

void Matrice::removeAt(int indexLin, int indexCol){             //ne folosim de cele doua metode deja create
    this->removeLineAt(indexLin);
    this->removeColAt(indexCol);
}



Matrice& Matrice::operator=(const Matrice& mat){
    this->noLinii=mat.noLinii;
    this->noCol=mat.noCol;
    this->prim = mat.prim;
    this->ultim = mat.ultim;
}

Matrice& Matrice::operator+(const Matrice& mat){
    if(this->noLinii != mat.noLinii || this->noCol != mat.noCol){
        //arunca exceptie de matrici inegale
    }else{
        Matrice *aux = new Matrice(*this);
        Matrice *Mat = new Matrice(mat);
        Matrice *toReturn = new Matrice(aux->getNoLinii(),aux->getNoCol());

        for(int i=0;i<mat.noLinii;i++){
            Linie *linieMat = new Linie((*Mat)[i]);
            Linie *linieThis = new Linie((*aux)[i]);
            Linie *linieToReturn = new Linie();
            Element *elemMat = linieMat->getPrim();
            Element *elemThis = linieThis->getPrim();

            for(int j=0;j<linieMat->getLength();j++){
                linieToReturn->pushRight(elemThis->getInfo()+elemMat->getInfo());
                elemMat = elemMat->getNext();
                elemThis = elemThis->getNext();
            }

            toReturn->insertLine(*linieToReturn);
            linieMat= linieMat->getNext();
            linieThis = linieThis->getNext();
        }
        return *toReturn;
    }
}

Linie& Matrice::operator[](int index){
    if(index >= this->noLinii){
        //arunca exceptie de index out of range
    }else{
        Linie *aux = this->prim;
        for(int i=0;i<index;i++){
            aux = aux->getNext();
        }
        return *aux;
    }
}

Matrice& Matrice::operator-(const Matrice& mat){
    if(this->noLinii != mat.noLinii || this->noCol != mat.noCol){
        //arunca exceptie de matrici inegale
    }else{
        Matrice *aux = new Matrice(*this);
        Matrice *Mat = new Matrice(mat);
        Matrice *toReturn = new Matrice(aux->getNoLinii(),aux->getNoCol());

        for(int i=0;i<mat.noLinii;i++){
            Linie *linieMat = new Linie((*Mat)[i]);
            Linie *linieThis = new Linie((*aux)[i]);
            Linie *linieToReturn = new Linie();
            Element *elemMat = linieMat->getPrim();
            Element *elemThis = linieThis->getPrim();

            for(int j=0;j<linieMat->getLength();j++){
                linieToReturn->pushRight(elemThis->getInfo()-elemMat->getInfo());
                elemMat = elemMat->getNext();
                elemThis = elemThis->getNext();
            }

            toReturn->insertLine(*linieToReturn);
            linieMat= linieMat->getNext();
            linieThis = linieThis->getNext();
        }
        return *toReturn;
    }
}

Matrice& Matrice::operator*(int scalar){

    Matrice *aux = new Matrice(*this);
    Matrice *toReturn = new Matrice(aux->getNoLinii(),aux->getNoCol());

    for(int i=0;i<aux->noLinii;i++){
        Linie *linieThis = new Linie((*aux)[i]);
        Linie *linieToReturn = new Linie();
        Element *elemThis = linieThis->getPrim();

        for(int j=0;j<linieThis->getLength();j++){
            linieToReturn->pushRight(elemThis->getInfo()*scalar);
            elemThis = elemThis->getNext();
        }
        toReturn->insertLine(*linieToReturn);
        linieThis = linieThis->getNext();
    }
    return *toReturn;
}

Matrice& Matrice::operator*(Matrice& mat){
    if(this->getNoCol() != mat.getNoLinii() ){
        //aruncam exceptie
    }else{

        Matrice *toReturn = new Matrice(this->getNoLinii(),mat.getNoCol(),true);

        for(int i = 0; i < this->getNoLinii(); i++){
            for(int j = 0; j < mat.getNoCol(); j++){
                for(int x = 0; x < this->getNoCol(); x++){
                    (*toReturn)[i][j].setInfo((*toReturn)[i][j].getInfo() + (*this)[i][x].getInfo() * mat[x][j].getInfo() );
                }
            }
        }
       return *toReturn;
    }
}


istream& operator>>(istream& in, Matrice& mat){
    /*if(mat.prim != NULL)
    {
        for(int i=0; i < mat.getNoLinii(); i++){
            mat.removeLineAt(0);
        }
    }*/

    for(int i=0;i<mat.getNoLinii();i++){
        Linie line;
        for(int j=0;j<mat.getNoCol();j++){
            int x;
            in>>x;
            line.pushRight(x);
        }
        mat.insertLine(line);
    }
    return in;
}

ostream& operator<<(ostream& out, const Matrice& mat){
    Linie *counter = mat.prim;
    for(int i=0;i<mat.noLinii;i++){
        out<<*counter;
        out<<endl;
        counter = counter->getNext();
    }
    return out;
}

Matrice::~Matrice(){
    cout<<"a fost stearsa"<<endl;
}



