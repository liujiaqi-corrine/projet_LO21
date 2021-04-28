#ifndef FRACTION_H_INCLUDED
#define FRACTION_H_INCLUDED
#include<iostream>
#include<string>
#include<vector>

#define MAX_STATE 8

using namespace std;

class State
{
    string label;
    string color;
public :
    State(string _label = "", string _color = ""): label(_label), color(_color){};
    ~State() = default;

    inline string getLabel() const{return label;}
    inline string getColor() const{return color;}
};

class Cell
{
    int x;
    int y;
    State* state;
public :
    Cell() = default;
    ~Cell() = default;
    Cell(int X, int Y): x(X), y(Y), state(nullptr){};

    inline int getX() const{return x;}
    inline int getY() const{return y;}
    inline State* getState() const{return state;}
};

class Grid
{
    int length;
    int width;
    vector<Cell*> *grid;
public :
    Grid() = default;
    ~Grid() = default;
    Grid(int _length, int _width): length(_length), width(_width), grid(nullptr){};

    inline int getLength() const{return length;}
    inline int getWidth() const{return width;}
};

class Rule
{
public :
    Rule() = default;
    ~Rule() = default;
};

class Voisinage
{
    string name;
    int radius;
    Rule* rule;
public :
    Voisinage() = default;
    ~Voisinage() = default;
};

class Model
{
    string name;
    vector<State*>* listStates;
    Voisinage* voisinage;
public :
    Model();
    ~Model() = default;

    inline string getName() const{return name;}
    inline void setName(string _name){name = _name;}
    inline vector<State*>* getListStates() const{return listStates;}

    void addState(string label, string color);
    void delState(int index);

};

class Library
{
    vector<Model*> *library;
public :
    Library() = default;
    ~Library() = default;

    Model getModel();
    void addModel(Model X);
    void delModel();
};

#endif // CELLULUT_H_INCLUDED
