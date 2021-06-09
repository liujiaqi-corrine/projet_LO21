#include "main.h"
#include "models/Surrounding.h"

Surrounding::Surrounding(string _name, unsigned int _diameter, bool** _interaction): name(_name), diameter(_diameter), interaction(_interaction){}


string Surrounding::getName() const{return this->name;}

unsigned int Surrounding::getDiameter() const{return this->diameter;}

bool** Surrounding::getInteraction() const{return this->interaction;}


void Surrounding::setName(string _name){this->name = _name;}

void Surrounding::setDiameter(unsigned int _diameter){this->diameter = _diameter;}

void Surrounding::setInteraction(bool **_interaction){this->interaction = _interaction;}
