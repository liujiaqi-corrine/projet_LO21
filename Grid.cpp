#include "Grid.h"
#include "Model.h"

//Grid::Grid(unsigned int _length, unsigned int _width) : length(_length), width(_width){};

Grid::Grid(int rows, int columns, QWidget *parent) : QTableWidget(rows, columns, parent) {

    //length = rows;
    //width = columns;
    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->resizeColumnsToContents();
    this->resizeRowsToContents();
    //this->horizontalHeader()->setStretchLastSection(true);
    //this->verticalHeader()->setStretchLastSection(true);

    model = new Model();

    listCells = new Cell**[rows];
    for (int i=0; i<rows; i++){
        listCells[i] = new Cell*[columns];
        for (int j=0; j<columns; j++) {
            listCells[i][j] = new Cell(i,j);
            this->setItem(i,j,listCells[i][j]);
            listCells[i][j]->setState((model->getListStates()[0]));
            listCells[i][j]->setBackground(QBrush(listCells[i][j]->getState()->getColor()));
        }
    }


    //this->item(5,4)->setBackground(QBrush(QColor(Qt::magenta)));
    //listCells[4*5+5]->setBackground(QBrush(QColor(Qt::yellow)));


    QObject::connect(this,&Grid::cellClicked,this,&Grid::changeState);

}

void Grid::changeState(int row, int column){


    int i = this->listCells[row][column]->getState()->getIndex();

    this->listCells[row][column]->setState(model->getListStates()[(i+1)%model->getNbState()]);

    this->listCells[row][column]->setBackground(QBrush(listCells[row][column]->getState()->getColor()));

    listCells[row][column]->setText(listCells[row][column]->getState()->getLabel()[0]);

}

/*void Grid::deblockCells(){

    for (unsigned int i=0; i<width; i++){
        for (unsigned int j=0; j<length; j++){
            listCells[j*i+i]->setFlags(Qt::ItemIsEnabled);
        }
    }


}*/

//int Grid::getLength() const{return length;}

//int Grid::getWidth() const{return width;}

Cell*** Grid::getlistCells() const{return listCells;}

void Grid::setlistCells(Cell*** _listCells) {listCells = _listCells;}

//void Grid::setLength(unsigned int _length) {length = _length;}

//void Grid::setWidth(unsigned int _width) {width = _width;}

void Grid::setModele(Model* _modele) {model = _modele;}
