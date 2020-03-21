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
    Matrice *subMat = new Matrice(this->getNoLinii(),this->getNoCol(),true);            //facem un pointer catre o matrice
    if(this->getNoCol() != this->getNoLinii()){                                         // daca matricea nu e patratica aruncam exceptie
        //aruncam exceptie
    }else if(this->getNoLinii() == 2){                                                  //cand ajungem la o matrice de 2x2 putem calcula determinantul
        return( ((*this)[0][0].getInfo()*(*this)[1][1].getInfo()) - ((*this)[1][0].getInfo()*(*this)[0][1].getInfo()));
    }else{
        for(int x = 0; x < this->getNoLinii(); x++){                                    //pentru fiecare linie din matricea care apeleaza
            int subi = 0;                                                               //contor pentru calcularea determinantilor interiori
            for(int i = 1; i < this->getNoLinii(); i++){                                //pentru fiecare linie din matricea care apeleaza
                int subj = 0;                                                           //contor pentru calcularea determinantilor interiori
                for(int j = 0 ; j < this->getNoLinii(); j++){                           //pentru fiecare linie din matricea care apeleaza
                    if(j == x)
                        continue;
                    ((*subMat)[subi][subj]).setInfo( (*this)[i][j].getInfo() );         //construim determinantii interiori
                    subj++;
                }
                subi++;
            }
            Matrice *aux = new Matrice(*subMat);                                        //pointer catre o matrice cu care vom apela recursiv metoda
            aux ->removeAt(aux->getNoLinii()-1,aux->getNoCol()-1);                      //stergem ultima linie si ultima coloana

            det = det + (pow(-1,x) * (*this)[0][x].getInfo() * aux->getDeterminant() ); //apelam recursiv metoda pana matricea ajunge sa fie de 2x2
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

Matrice& Matrice::operator=(const Matrice& mat){                //supraincarcarea operatorului =
    this->noLinii=mat.noLinii;
    this->noCol=mat.noCol;
    this->prim = mat.prim;
    this->ultim = mat.ultim;
}

Matrice& Matrice::operator+(const Matrice& mat){                                //supraincarcarea operatorului +
    if(this->noLinii != mat.noLinii || this->noCol != mat.noCol){               //verificam daca matricile sunt egale dpdv al noCol si noLinii
        //arunca exceptie de matrici inegale
    }else{
        Matrice *aux = new Matrice(*this);                                      //facem un pointer catre o matrice copiata dupa cea care apeleaza
        Matrice *Mat = new Matrice(mat);                                        //pentru a putea folosi ulterior supraincarcarea lui [] (care nu este const)
        Matrice *toReturn = new Matrice(aux->getNoLinii(),aux->getNoCol());

        for(int i=0;i<mat.noLinii;i++){                                         //parcurgem matricea din dreapta lui +
            Linie *linieMat = new Linie((*Mat)[i]);                             //pointer catre o copie a liniei cu indexul i a matricii din dreapta
            Linie *linieThis = new Linie((*aux)[i]);                            //pointer catre o copie a liniei cu indexul i a matricii din stanga
            Linie *linieToReturn = new Linie();
            Element *elemMat = linieMat->getPrim();                             //pointer catre primele elemente ale matricilor
            Element *elemThis = linieThis->getPrim();

            for(int j=0;j<linieMat->getLength();j++){                               //parcurgem liniile
                linieToReturn->pushRight(elemThis->getInfo()+elemMat->getInfo());   //introducem suma dintre cele 2 elemente in linia care va fi
                elemMat = elemMat->getNext();                                       //indrodusa in matricea care va fi returnata
                elemThis = elemThis->getNext();
            }
            toReturn->insertLine(*linieToReturn);                                   //introducem linia in matricea care va fi returnata
            linieMat= linieMat->getNext();
            linieThis = linieThis->getNext();
        }
        return *toReturn;
    }
}

Linie& Matrice::operator[](int index){                                          //suprascrierea operatorului []
    if(index >= this->noLinii){                                                 //verificam daca indexul este in matrice
        //arunca exceptie de index out of range
    }else{
        Linie *aux = this->prim;                                                //pointer catre prima linie din matrice
        for(int i=0;i<index;i++){                                               //parcurgem matricea
            aux = aux->getNext();
        }
        return *aux;                                                            //returnam valoarea din zona de memorie
    }                                                                           //pointata de pointer
}

Matrice& Matrice::operator-(const Matrice& mat){                                    //analog +
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
                linieToReturn->pushRight(elemThis->getInfo()-elemMat->getInfo());   //doar ca aici e -
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

Matrice& Matrice::operator*(int scalar){                                    //supraincarcarea operatorului * cu un scalar
    Matrice *toReturn = new Matrice(this->getNoLinii(),this->getNoCol());   //matricea care va fi returnata

    for(int i=0;i<this->noLinii;i++){                                       //parcurgem matricea care apeleaza
        Linie *linieThis = new Linie((*this)[i]);                           //facem un pointer catre o copie a liniei de pe indexul i
        Linie *linieToReturn = new Linie();                                 //facem un pointer catre o linie pe care o vom introduce in matricea de returnat
        Element *elemThis = linieThis->getPrim();                           //facem un pointer catre un element cu care vom parcurge linia

        for(int j=0;j<linieThis->getLength();j++){                          //pentru fiecare element din linie
            linieToReturn->pushRight(elemThis->getInfo()*scalar);           //il inmultim cu scalarul si il introducem in linia care va fi introdusa in
            elemThis = elemThis->getNext();                                 //matricea de returnat
        }
        toReturn->insertLine(*linieToReturn);                               //introducem linia in matricea de returnat
        linieThis = linieThis->getNext();                                   //trecem la urmatoarea linie
    }
    return *toReturn;
}

Matrice& Matrice::operator*(Matrice& mat){
    if(this->getNoCol() != mat.getNoLinii() ){
        //aruncam exceptie
    }else{

        Matrice *toReturn = new Matrice(this->getNoLinii(),mat.getNoCol(),true);                        //matricea finala are m1 linii si m2 col

        for(int i = 0; i < this->getNoLinii(); i++){                                                    //parcurgem liniile matricii din stanga
            for(int j = 0; j < mat.getNoCol(); j++){                                                    //parcurgem coloanele matricii din dreapta
                for(int x = 0; x < this->getNoCol(); x++){                                              //parcurgem fiecare element din linie si coloana pentru a le inmulti si aduna
                    (*toReturn)[i][j].setInfo((*toReturn)[i][j].getInfo() + (*this)[i][x].getInfo() * mat[x][j].getInfo() );
                }
            }
        }
       return *toReturn;
    }
}

istream& operator>>(istream& in, Matrice& mat){                 //suprascrierea operatorului >>
    for(int i=0;i<mat.getNoLinii();i++){                        //pentru fiecare linie
        Linie line;                                             //facem o linie noua
        for(int j=0;j<mat.getNoCol();j++){                      //pentru fiecare element din linie
            int x;                                              //citim informatia pentru element
            in>>x;
            line.pushRight(x);                                  //introducem valoarea in linie
        }
        mat.insertLine(line);                                   //introducem linia in matrice
    }
    return in;
}

ostream& operator<<(ostream& out, const Matrice& mat){          //suprascrierea operatorului <<
    Linie *counter = mat.prim;                                  //facem un pointer catre prima linie din matrice
    for(int i=0;i<mat.noLinii;i++){                             //parcurgem liniile matricii
        out<<*counter;                                          //trimitem valoarea din interiorul zonei de memorie
        out<<endl;                                              //pointata de pointerul counter pe fluxul de iesire
        counter = counter->getNext();                           // trecem la urmatoarea linie
    }
    return out;
}

Matrice::~Matrice(){                                            //destructor
    cout<<"a fost stearsa"<<endl;
}



