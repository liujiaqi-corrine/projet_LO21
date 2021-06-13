#include "main.h"
#include "models/Grid.h"

Grid* Grid::singleton = new Grid;

Grid::Grid(){
    this->mapCells = new map<string,Cell*>();

    qInfo() << "Grid::Grid - constructor";
}

unsigned int Grid::getSize() const{return this->size;}

map<string, Cell*>* Grid::getCells() const{return this->mapCells;}


void Grid::setSize(unsigned int _size){this->size = _size;}

void Grid::setCells(map<string, Cell*>* _cells){this->mapCells = _cells;}


void Grid::removeAllCells(){
    map<string,Cell*>::iterator it;
    for(map<std::string, Cell*>::iterator itr = this->mapCells->begin(); itr != this->mapCells->end(); itr++)
    {
        delete (itr->second);
    }
    this->mapCells->clear();
}

map<int,int> Grid::countNbCellsPerState(){
    map<int,int> nbCellsPerState;
    for(map<std::string, Cell*>::iterator itr = this->mapCells->begin(); itr != this->mapCells->end(); itr++)
    {
        Cell *cell = itr->second;
        int stateIndex = cell->getState()->getIndex();
        int nbStates;
        if(nbCellsPerState.count(stateIndex) == 0){
            nbStates = 1;
        } else {
            nbStates = nbCellsPerState.at(stateIndex);
            nbStates++;
        }
        nbCellsPerState.insert({stateIndex,nbStates});
        cout<<nbStates<<endl;
    }

    return nbCellsPerState;
}
