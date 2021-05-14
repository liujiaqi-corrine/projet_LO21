#include "State.h"

State::State(QString _label, QString _color, int _index): label(_label), color(_color), index(_index){}

QString State::getLabel() const{return label;}

QString State::getColor() const{return color;}

int State::getIndex() const{return index;}

void State::setIndex(int _index){index = _index;}
