#include "Cellulut.h"

State::State(string _label, string _color, int _index): label(_label), color(_color), index(_index){}

string State::getLabel() const{return label;}

string State::getColor() const{return color;}
