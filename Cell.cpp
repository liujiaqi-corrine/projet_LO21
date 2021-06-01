#include "Cell.h"


Cell::Cell(int _x, int _y, int type) : QTableWidgetItem(type) {

    x= _x;
    y= _y;
    //this->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
    //this->setFlags(Qt::ItemIsEnabled);
    this->setFlags(Qt::NoItemFlags);
    this->setText("o");

    state = nullptr;


    //state = new State(0, QColor(Qt::white));  // Remettre en blanc plus tard

    //this->setBackground(QBrush(state->getColor()));

}


int Cell::getX() const{return x;}

int Cell::getY() const{return y;}

State* Cell::getState() const{return state;}

void Cell::setX(int _x){x = _x;}

void Cell::setY(int _y){y = _y;}

void Cell::setState(State* _state){state = _state; this->setText(state->getLabel()[0]);}
