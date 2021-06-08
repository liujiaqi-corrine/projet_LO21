#include "main.h"
#include "models/Rule.h"

Rule_int::Rule_int(unsigned int _A, unsigned int _B, unsigned int _C, unsigned int _D)
{
    this->list = new unsigned int[4];
    list[0] = _A;
    list[1] = _B;
    list[2] = _C;
    list[3] = _D;
}

unsigned int Rule_int::getRule_current_state() const{return this->list[0];}

unsigned int Rule_int::getRule_nb_nearby() const{return this->list[1];}

unsigned int Rule_int::getRule_state_nearby() const{return this->list[2];}

unsigned int Rule_int::getRule_next_state() const{return this->list[3];}


void Rule_int::setRule_current_state(unsigned int _current_state){this->list[0] = _current_state;}

void Rule_int::setRule_nb_nearby(unsigned int _nb_nearby){this->list[1] = _nb_nearby;}

void Rule_int::setRule_state_nearby(unsigned int _state_nearby){this->list[2] = _state_nearby;}

void Rule_int::setRule_next_state(unsigned int _next_state){this->list[3] = _next_state;}
