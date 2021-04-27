#ifndef FRACTION_H_INCLUDED
#define FRACTION_H_INCLUDED
#include<iostream>
#include<string>

using namespace std;

class State{
    int index;
    string label;
    string color;
public :
    State(string _label = "", string _color = "", int _index = 0): label(_label), color(_color), index(_index){};
    ~State() = default;

    inline int getIndex() const{return index;}
    inline string getLabel() const{return label;}
    inline string getColor() const{return color;}
};

class Cell{
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

class Grid{
    int length;
    int width;
    Cell** grid;
public :
    Grid() = default;
    ~Grid() = default;
    Grid(int _length, int _width): length(_length), width(_width), grid(nullptr){};

    inline int getLength() const{return length;}
    inline int getWidth() const{return width;}
};

class Rule{
public :
    Rule() = default;
    ~Rule() = default;
};

class Voisinage{
    string name;
    int radius;
    Rule* rule;
public :
    Voisinage() = default;
    ~Voisinage() = default;
};

struct Model{
    string name;
    State** groupState;
    int nb_state;
    Voisinage* voisinage;
public :
    Model();
    ~Model() = default;

    inline void addState(string label, string color){
        State test(label,color,nb_state);
        groupState[nb_state++] = &test;
    };

    void delState(int index);

};

struct Library{
    Model** library = new Model*;
public :
    Library() = default;
    ~Library() = default;

    Model getModel();
    void addModel(Model X);
    void delModel();
};

#endif // CELLULUT_H_INCLUDED
