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

    inline void setState(State* _state){state = _state;}
};

class Grid
{
    unsigned int length;
    unsigned int width;
    Cell** listCells;
public :
    inline Grid(unsigned int _length = 0, unsigned int _width = 0) : length(_length), width(_width){};
    ~Grid() = default;

    inline unsigned int getLength() const{return length;}
    inline unsigned int getWidth() const{return width;}
    inline Cell** getlistCells() const{return listCells;}

    inline void setlistCells(Cell** _listCells) {listCells = _listCells;}
    inline void setLength(unsigned int _length) {length = _length;}
    inline void setWidth(unsigned int _width) {width = _width;}
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
    Grid* grid;
    //Voisinage* voisinage;
public :
    Model();
    ~Model() = default;

    inline string getName() const{return name;}
    inline void setName(string _name){name = _name;}
    inline vector<State*>* getListStates() const{return listStates;}
    inline Grid* getGrid() const{return grid;}

    void init_Grid(int width, int length);
    void add_State(string label, string color);
    void del_State(int index);

};

class Library
{
    static Library* singleton;  //Pointeur vers le singleton
    Library() = default;  //Constructeur privé
    vector<Model*> *library;
public :
    static Library* get() noexcept
    {
        return singleton;
    }
    ~Library() = default;

    Model getModel();
    void add_Model(Model X);
    void del_Model();
};

#endif // CELLULUT_H_INCLUDED
