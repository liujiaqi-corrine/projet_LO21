#include "main.h"
#include "models/State.h"

State::State(unsigned int _index, string _color, string _label): index(_index), color(_color), label(_label){}


unsigned int State::getIndex() const{return this->index;}

string State::getColor() const{return this->color;}

string State::getLabel() const{return this->label;}


void State::setIndex(unsigned int _index){this->index=_index;}

void State::setColor(string _color){this->color = _color;}

void State::setLabel(string _label){this->label=_label;}


QString State::getColorAsQString() const{return QString::fromUtf8(this->color.c_str());}

QString State::getLabelAsQString() const{return QString::fromUtf8(this->label.c_str());}
