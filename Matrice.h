#include"Linie.h"
using namespace std;

class Matrice{
    Linie* prim,*ultim;                     //pointeri catre prima si ultima linie din matrice
    int noLinii;
    int noCol;
    void insertLine(Linie);
public:
    Matrice(int,int, bool zeros=false);     //constructor cu parametrii ,al treilea parametru daca este true initializeaza matricea cu 0
    Matrice(const Matrice&);                // constructor de copiere
    int getNoLinii();
    int getNoCol();
    float getDeterminant();
    bool isInvertible();
    void removeLineAt(int);
    void removeColAt(int);
    void removeAt(int,int);                 //metoda care sterge o lininie si o coloana dintr-o matrice

    Matrice& operator=(const Matrice &mat); //supraincarcari de operatori
    Matrice& operator+(const Matrice &mat);
    Linie& operator[](int);
    Matrice& operator-(const Matrice &mat);
    Matrice& operator*(int);
    Matrice& operator*(Matrice&);
    friend istream& operator>>(istream&,Matrice&);
    friend ostream& operator<<(ostream&,const Matrice&);

    ~Matrice();

};
