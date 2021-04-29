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
            grid->getlistCells()[i][j].setState(listStates->at(0));
        }
    }
}

void Model::add_State(State* new_state)
{
    if( listStates->size() < MAX_STATE)
    {
        this->listStates->push_back(new_state);
    }
    else
    {
        cout<<"Maximum number of states reached"; //Gestion d'exception à faire
        return;
    }
}

void Model::del_State(int index)
{

}
