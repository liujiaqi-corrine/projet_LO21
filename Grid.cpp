#include "Grid.h"

//Grid::Grid(unsigned int _length, unsigned int _width) : length(_length), width(_width){};

Grid::Grid(int rows, int columns, QWidget *_parent) : QTableWidget(rows, columns, _parent) {

    parent = (Automate*) _parent;
    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->resizeColumnsToContents();
    this->resizeRowsToContents();

    listCells = new Cell**[rows];
    for (int i=0; i<rows; i++){
        listCells[i] = new Cell*[columns];
        for (int j=0; j<columns; j++) {
            listCells[i][j] = new Cell(i,j);
            this->setItem(i,j,listCells[i][j]); // Obligation de setItem sinon pas content
            listCells[i][j]->setState((parent->getLib()->getCurrentModel()->getListStates()[0])); //affiche aussi la 1er lettre du label
            listCells[i][j]->setBackground(QBrush(listCells[i][j]->getState()->getColor()));
        }
    }


    //this->item(5,4)->setBackground(QBrush(QColor(Qt::magenta)));
    //listCells[4*5+5]->setBackground(QBrush(QColor(Qt::yellow)));


    QObject::connect(this,&Grid::cellClicked,this,&Grid::changeState);

}



void Grid::changeState(int row, int column){


    int i = this->listCells[row][column]->getState()->getIndex();

    this->listCells[row][column]->setState(parent->getLib()->getCurrentModel()->getListStates()[(i+1)%parent->getLib()->getCurrentModel()->getNbState()]);

    this->listCells[row][column]->setBackground(QBrush(listCells[row][column]->getState()->getColor()));

    listCells[row][column]->setText(listCells[row][column]->getState()->getLabel()[0]);
    //listCells[row][column]->setText(QString::number(listCells[row][column]->getState()->getIndex()));

}

void Grid::resetGrid(){

    for (int i=0; i<rowCount(); i++){
        for (int j=0; j<columnCount(); j++) {
    listCells[i][j]->setState((parent->getLib()->getCurrentModel()->getListStates()[0]));
    listCells[i][j]->setBackground(QBrush(listCells[i][j]->getState()->getColor()));
        }
    }



}

void Grid::updateGrid(Cell*** newCells){

    //apres penser à save listCells pour l'historique

    listCells=newCells;

    for (int i=0; i<rowCount(); i++){
        for (int j=0; j<columnCount(); j++) {
            this->setItem(i,j, listCells[i][j]);
            listCells[i][j]->setBackground(QBrush(listCells[i][j]->getState()->getColor()));
        }
    }


};

Grid::Grid(int size, QWidget* _parent) : QTableWidget(size, size, _parent) {
    parent = dynamic_cast<Automate*> (_parent);
    this->horizontalHeader()->setVisible(false);
    this->verticalHeader()->setVisible(false);
    this->setSelectionMode(QAbstractItemView::SingleSelection);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->resizeColumnsToContents();
    this->resizeRowsToContents();
    listCells = new Cell**[size];
    for (int i=0; i<size; i++){
        listCells[i] = new Cell*[size];
        for (int j=0; j<size; j++) {
            listCells[i][j] = new Cell(i,j);
            this->setItem(i,j,listCells[i][j]);
            listCells[i][j]->setState((parent->getLib()->getCurrentModel()->getListStates()[0]));
            listCells[i][j]->setBackground(QBrush(parent->getLib()->getCurrentModel()->getListStates()[0]->getColor()));
        }
    }
    QObject::connect(this,&Grid::cellClicked,this,&Grid::changeState);
}

/*void Grid::changeStateSurrounding(int row, int column){
    int i = this->listCells[row][column]->getState()->getIndex();
    this->listCells[row][column]->setState(modelBase->getListStates()[(i+1)%modelBase->getNbState()]);
    this->listCells[row][column]->setBackground(QBrush(listCells[row][column]->getState()->getColor()));
    listCells[row][column]->setText(listCells[row][column]->getState()->getLabel()[0]);
}*/

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

//void Grid::setModele(Model* _modele) {model = _modele;}
