#include <iostream>
#include <fstream>
#include "Matrice.h"

using namespace std;

int main()
{
    ifstream input;
    input.open("input.txt");

    //testare citire + scriere :
    Matrice m1(5,5);
    input>>m1;
    cout<<"afisare matrice:"<<endl;
    cout<<m1<<endl;

    //testare supraincarcare + :
    Matrice m2(3,3), m3(3,3);
    input>>m2>>m3;
    cout<<"matrice 1:"<<endl<<m2<<"matrice 2:"<<endl<<m3;
    cout<<"matrice 1 + matrice 2: "<<endl;
    cout<<m2+m3;
    cout<<"-----------------------------------------"<<endl;

    //testare supraincarcare [] :
    cout<<"linia 2 a matricii 1 este:"<<endl;
    cout<<m2[2];

    //testare supraincarcare - :
    cout<<endl;
    cout<<"matrice 1 - matrice 2: "<<endl;
    cout<<m2-m3;

    //testare supraincarcare * :
    cout<<"matrice 1 * matrice 2: "<<endl;
    cout<<m2*m3;
    cout<<"matricea 1 * 3: "<<endl;
    cout<<m2*3;

    //testare determinant si inversabilitate :
    cout<<"det(matrice 1): "<<endl;
    cout<<m2.getDeterminant()<<endl;
    cout<<"matricea "<<(m2.isInvertible()?"este ":"nu este ")<<"inversabila"<<endl<<endl;

    //testare metode remove linie/coloana/ambele si obtinerea numarukui de linii si de coloane:
    Matrice m4(5,5);
    cout<<"-----------------------------------------"<<endl;
    cout<<"matrice pentru sters, are "<<m4.getNoLinii()<<" linii si "<<m4.getNoCol()<<" coloane"<<endl;
    input>>m4;
    cout<<m4;
    cout<<"stergem linia 1"<<endl;
    m4.removeLineAt(1);
    cout<<m4;
    cout<<"acum matricea are "<<m4.getNoLinii()<<" linii si "<<m4.getNoCol()<<" coloane"<<endl;
    cout<<"stergem coloana 2"<<endl;
    m4.removeColAt(2);
    cout<<m4;
    cout<<"acum matricea are "<<m4.getNoLinii()<<" linii si "<<m4.getNoCol()<<" coloane"<<endl;
    cout<<"stergem linia 3 si coloana 1"<<endl;
    m4.removeAt(3,1);
    cout<<m4;
    cout<<"acum matricea are "<<m4.getNoLinii()<<" linii si "<<m4.getNoCol()<<" coloane"<<endl;
    cout<<"-----------------------------------------"<<endl;

    //testare cerinte globale:

    //testare constructor de copiere si verificarea unicitatii in memorie:
    cout<<"testare constructor de copiere si verificarea unicitatii in memorie:"<<endl;
    Matrice mat1 (3,4);
    input>>mat1;
    Matrice mat2 = mat1;

    cout<<mat2;
    mat1.removeAt(1,1);
    cout<<endl;
    cout<<mat2;






    input.close();

    return 0;

}
