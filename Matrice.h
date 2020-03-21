#include"Linie.h"
using namespace std;

class Matrice{
    Linie* prim,*ultim;
    int noLinii;
    int noCol;
    void insertLine(Linie);
public:
    Matrice(int,int, bool zeros=false);
    Matrice(const Matrice&);

    //Matrice remove(Linie*,int);
    int getNoLinii();
    int getNoCol();
    float getDeterminant();
    bool isInvertible();
    void removeLineAt(int);
    void removeColAt(int);
    void removeAt(int,int);

    Matrice& operator=(const Matrice &mat);
    Matrice& operator+(const Matrice &mat);
    Linie& operator[](int);
    Matrice& operator-(const Matrice &mat);
    Matrice& operator*(int);
    Matrice& operator*(Matrice&);
    friend istream& operator>>(istream&,Matrice&);
    friend ostream& operator<<(ostream&,const Matrice&);


};
