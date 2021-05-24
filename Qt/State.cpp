#include "State.h"

State::State(int _index, QColor _color, QString _label){

    index = _index;
    label = _label;
    color = _color;
    //color = QColor(Qt::blue);

}

QString State::getLabel() const{return label;}

QColor State::getColor() const{return color;}

int State::getIndex() const{return index;}

void State::setIndex(int _index){index = _index;}
