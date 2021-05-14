#include "Grid.h"

Grid::Grid(unsigned int _length, unsigned int _width) : length(_length), width(_width){};

Grid::Grid(int rows, int columns, QWidget *parent) : QTableWidget(rows, columns, parent) {

    length = rows;
    width = columns;
    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->resizeColumnsToContents();
    this->resizeRowsToContents();
    //this->horizontalHeader()->setStretchLastSection(true);
    //this->verticalHeader()->setStretchLastSection(true);

    listCells = new Cell*[rows*columns];

    for (int i=0; i<columns; i++){
        for (int j=0; j<rows; j++){
            listCells[j*i+i] = new Cell();
            this->setItem(i,j,listCells[j*i+i]);
        }
    }

    QObject::connect(this,&Grid::cellClicked,this,&Grid::faire);

}

void Grid::faire(int columns, int rows){

    this->item(columns, rows)->setText("f");

}

unsigned int Grid::getLength() const{return length;}

unsigned int Grid::getWidth() const{return width;}

Cell** Grid::getlistCells() const{return listCells;}

void Grid::setlistCells(Cell** _listCells) {listCells = _listCells;}

void Grid::setLength(unsigned int _length) {length = _length;}

void Grid::setWidth(unsigned int _width) {width = _width;}
