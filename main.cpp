#include <iostream>
#include <fstream>
#include "Matrice.h"

using namespace std;

int main()
{
    ifstream input;
    input.open("input.txt");

    Matrice m1(5,5);
    input >>m1;

    cout<<m1;
    cout<<m1.getDeterminant();
    cout<<endl;
    cout<<m1.isInvertible();
   //cout<<getDeterminant(m1,m1.getNoLinii());

    cout<<endl;
    Matrice m2(3,3),m3(3,3);
    input>>m2;
    input>>m3;
    cout<<m2*m3;


    return 0;

}
