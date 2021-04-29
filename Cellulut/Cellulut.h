#ifndef FRACTION_H_INCLUDED
#define FRACTION_H_INCLUDED

#include<iostream>
#include<string>
#include<vector>

#define MAX_STATE 8

using namespace std;

class State
{
    protected :
        string label;
        string color;
        int index;
    public :
        State(string _label = "", string _color = "", int _index = 0);
        ~State() = default;

        string getLabel() const;
        string getColor() const;
};

class Cell
{
    protected :
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
    protected :
        unsigned int length;
        unsigned int width;
        Cell** listCells;
    public :
        Grid(unsigned int _length = 0, unsigned int _width = 0);
        ~Grid() = default;

        unsigned int getLength() const;
        unsigned int getWidth() const;
        Cell** getlistCells() const;

        void setlistCells(Cell** _listCells);
        void setLength(unsigned int _length);
        void setWidth(unsigned int _width);
};

class Rule
{
    protected :
    public :
        Rule() = default;
        ~Rule() = default;
};

class Voisinage
{
    protected :
        string name;
        int radius;
        Rule* rule;
    public :
        Voisinage() = default;
        ~Voisinage() = default;
};

class Model
{
    protected :
        string name;
        vector<State*>* listStates;
        Grid* grid;
        //Voisinage* voisinage;
    public :
        Model(string _name = "");
        ~Model() = default;

        string getName() const;
        vector<State*>* getListStates() const;
        Grid* getGrid() const;

        void setName(string _name);

        void init_Grid(int width, int length);
        void add_State(State* new_state);
        void del_State(int index);

        friend class Library;

};

class Library
{
    protected :
        static Library *singleton;  //Pointeur vers le singleton
        Library() = default;  //Constructeur privé
        vector<Model*>* listModels = new vector<Model*>;
    public :
        static Library* getInstance() noexcept
        {
            return singleton;
        }
        ~Library() = default;
        Library(const Library&) = delete;
        Library& operator=(const Library&) = delete;

        vector<Model*>* getListModels();
        Model* getModel();
        void add_Model(Model* new_model);
        void del_Model(Model* _model);
};

#endif // CELLULUT_H_INCLUDED
