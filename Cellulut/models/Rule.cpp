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



Rule_ext::Rule_ext(unsigned int _index, unsigned int _radius) : next_state_index(_index), radius(_radius)
{
    this->current_config = new vector<int>;
}

vector<int>* Rule_ext::getCurrent_config() const{return this->current_config;}

unsigned int Rule_ext::getNext_state_index() const{return this->next_state_index;}

unsigned int Rule_ext::getRadius() const{return this->radius;}


void Rule_ext::setCurrent_config(vector<int>* _config){this->current_config = _config;}

void Rule_ext::setNext_state_index(unsigned int _index){this->next_state_index = _index;}

void Rule_ext::setRadius(unsigned int _radius){this->radius = _radius;}

void Rule_ext::afficher_rule_ext()
{
    unsigned int size = this->radius * 2 + 1;
    for (unsigned int i = 0; i < size; i++)
    {
        for (unsigned int j = 0; j < size; j++)
        {
            cout<<this->current_config->at(i*size+j)<<" ";
        }
        cout << endl;
    }
    return;
}

void Rule_ext::addConfigLine(vector<int> _configLine){
    for(unsigned int i = 0; i < _configLine.size() ; i++){
        this->current_config->push_back(_configLine.at(i));
    }
    return;
}
