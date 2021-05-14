#include "Cell.h"

Cell::Cell(int type) : QTableWidgetItem(type) {

    //this->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    this->setFlags(Qt::ItemIsEnabled);
    this->setText("o");


}


int Cell::getX() const{return x;}

int Cell::getY() const{return y;}

State* Cell::getState() const{return state;}

void Cell::setX(int _x){x = _x;}

void Cell::setY(int _y){y = _y;}

void Cell::setState(State* _state){state = _state;}
