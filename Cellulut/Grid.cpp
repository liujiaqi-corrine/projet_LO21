#include "Grid.h"
#include "Model.h"

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
            listCells[j*i+i] = new Cell(i,j);
            this->setItem(i,j,listCells[j*i+i]);
        }
    }

    model = new Model("test",2);


    QObject::connect(this,&Grid::cellClicked,this,&Grid::changeState);

}

void Grid::changeState(int columns, int rows){



    int i = this->listCells[columns*rows+rows]->getState()->getIndex();

    this->listCells[columns*rows+rows]->setState(model->getListStates()[(i+1)%model->getNbState()]);

    this->item(columns, rows)->setBackground(QBrush(listCells[columns*rows+rows]->getState()->getColor()));



    //this->item(columns, rows)->setText("f");

}

/*void Grid::deblockCells(){

    for (unsigned int i=0; i<width; i++){
        for (unsigned int j=0; j<length; j++){
            listCells[j*i+i]->setFlags(Qt::ItemIsEnabled);
        }
    }


}*/

unsigned int Grid::getLength() const{return length;}

unsigned int Grid::getWidth() const{return width;}

Cell** Grid::getlistCells() const{return listCells;}

void Grid::setlistCells(Cell** _listCells) {listCells = _listCells;}

void Grid::setLength(unsigned int _length) {length = _length;}

void Grid::setWidth(unsigned int _width) {width = _width;}

void Grid::setModele(Model* _modele) {model = _modele;}
