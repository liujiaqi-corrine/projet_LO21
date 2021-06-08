#include "main.h"
#include "models/Grid.h"

Grid* Grid::singleton = new Grid;

unsigned int Grid::getRows() const{return this->rows;}

unsigned int Grid::getColumns() const{return this->columns;}

Cell** Grid::getlistCells() const{return listCells;}


void Grid::setRows(unsigned int _rows){this->rows = _rows;}

void Grid::setColumns(unsigned int _columns){this->columns = _columns;}

void Grid::setlistCells(Cell** _listCells) {listCells = _listCells;}
