#include "main.h"
#include "models/Cell.h"

int Cell::getX() const{return this->x;}

int Cell::getY() const{return this->y;}

State* Cell::getState() const{return this->state;}


void Cell::setX(int _x){this->x = _x;}

void Cell::setY(int _y){this->y = _y;}

void Cell::setState(State* _state){this->state = _state;}

string Cell::getHash() const {return to_string(x)+"-"+to_string(y);}

string Cell::getHashFromPos(int posX, int posY) {return to_string(posX)+"-"+to_string(posY);}
