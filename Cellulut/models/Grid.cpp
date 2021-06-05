#include "main.h"
#include "models/Grid.h"

Grid::Grid(int rows,int columns){
    setRowCount(rows);
    setColumnCount(columns);
};

Cell** Grid::getlistCells() const{return listCells;}

void Grid::setlistCells(Cell** _listCells) {listCells = _listCells;}
