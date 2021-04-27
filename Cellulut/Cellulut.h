#ifndef FRACTION_H_INCLUDED
#define FRACTION_H_INCLUDED
#include<iostream>
#include<string>

using namespace std;

struct Etat{
    int index;
    string label;
    string color;
public :
    Etat() = default;
    Etat(int X = 0, string Y = "", string Z = ""): index(X), label(Y), color(Z){};
    ~Etat() = default;
};

class Cellule{
    int x;
    int y;
    Etat* etat;
public :
    Cellule() = default;
    ~Cellule() = default;
    Cellule(int X, int Y): x(X), y(Y), etat(nullptr){};

    inline int getX() const{return x;}
    inline int getY() const{return y;}
    inline Etat* getEtat() const{return etat;}
};

class Grid{
    int length;
    int width;
    Cellule** grid;
public :
    Grid() = default;
    ~Grid() = default;
    Grid(int X, int Y): length(X), width(Y), grid(nullptr){};

    inline int getLength() const{return length;}
    inline int getWidth() const{return width;}
};

class Regle{
public :
    Regle() = default;
    ~Regle() = default;
};

class Voisinage{
    string name;
    int rayon;
    Regle* regle;
public :
    Voisinage() = default;
    ~Voisinage() = default;
};

struct Configuration{
    string name;
    Voisinage* voisinage;
    Etat* ensembleEtat = new Etat(8);
public :
    //Configuration() = default;
    Configuration(string X ="", Voisinage* Y = nullptr){
        Etat default_etat(0,"default","blanc");
        ensembleEtat[0] = default_etat;
    };
    ~Configuration() = default;

    addEtat();
    delEtat();

};

class Bibliotheque{
    Configuration** biblio;
public :
    Bibliotheque() = default;
    ~Bibliotheque() = default;

    getConfiguration();
    addConfiguration();
    delConfiguration();
};

#endif // CELLULUT_H_INCLUDED
