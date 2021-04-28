#include "Cellulut.h"

Model::Model()
{
    name = "";
    listStates = new vector<State*>;
    grid = new Grid();
    //voisinage = nullptr;
    add_State("defaut","blanc");
}

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

void Model::add_State(string label, string color)
{
    if( listStates->size() < MAX_STATE)
    {
        State* newState = new State(label,color);
        this->listStates->push_back(newState);
    }
}

Library *Library::singleton = new Library;

