#include "main.h"

Grid::Grid(unsigned int _length, unsigned int _width) : length(_length), width(_width){};

unsigned int Grid::getLength() const{return length;}

unsigned int Grid::getWidth() const{return width;}

Cell** Grid::getlistCells() const{return listCells;}

void Grid::setlistCells(Cell** _listCells) {listCells = _listCells;}

void Grid::setLength(unsigned int _length) {length = _length;}

void Grid::setWidth(unsigned int _width) {width = _width;}
