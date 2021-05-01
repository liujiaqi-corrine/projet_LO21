#include "Cellulut.h"

Model::Model(string _name)
{
    name = _name;
    listStates = new vector<State*>;
    grid = new Grid();
    //voisinage = nullptr;
    State* default_state = new State("default","white");
    add_State(default_state);
}

string Model::getName() const{return name;}

void Model::setName(string _name){name = _name;}

vector<State*>* Model::getListStates() const{return listStates;}

Grid* Model::getGrid() const{return grid;}

void Model::init_Grid(int width, int length)
{

    grid->setWidth(width);
    grid->setLength(length);
    grid->setlistCells(new Cell*[width]);
    for (int i=0; i < width; i++)
    {
        grid->getlistCells()[i] = new Cell[length];
    }
    for (int i=0; i < width; i++)
    {
        for (int j=0; j < length; j++)
        {
            grid->getlistCells()[i][j].setX(i);
            grid->getlistCells()[i][j].setY(j);
            grid->getlistCells()[i][j].setState(listStates->at(0));
        }
    }
}

void Model::add_State(State* new_state)
{
    if(listStates->size() >= MAX_STATE)
    {
        throw out_of_range("Maximum number of states reached");
    }
    for (int i =0; i < listStates->size(); i++)
    {
        if(listStates->at(i)->getIndex() == new_state->getIndex())
        {
            throw invalid_argument("State index already exists, index : " + to_string(new_state->getIndex()));
        }
    }
    this->listStates->push_back(new_state);
    cout<<"State added \n";
}

void Model::del_State(State* _state)
{
    for(int i = 0; i < listStates->size(); i++)
    {
        if(listStates->at(i) == _state)
        {
            listStates->erase(listStates->begin()+i);
            cout<<"State deleted"<<endl;
            return;
        }
    }
}

