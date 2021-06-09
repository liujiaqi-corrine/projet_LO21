#include "main.h"
#include "models/Surrounding.h"
#include "models/Library.h"

Surrounding::Surrounding(unsigned int _id_surrounding, string _name, unsigned int _radius): id_surrounding(_id_surrounding), name(_name), radius(_radius)
{
    this->id_surrounding = Library::getLibrary()->getListSurroundings()->size();
    this->interaction = new vector<bool>;
}

Surrounding::~Surrounding()
{
    delete[] this->interaction;
}

unsigned int Surrounding::getId_Surrounding() const{return this->id_surrounding;}

string Surrounding::getName() const{return this->name;}

unsigned int Surrounding::getRadius() const{return this->radius;}

vector<bool>* Surrounding::getInteraction() const{return this->interaction;}


void Surrounding::setName(string _name){this->name = _name;}

void Surrounding::setRadius(unsigned int _radius){this->radius = _radius;}

void Surrounding::setInteraction(vector<bool>*_interaction){this->interaction = _interaction;}

void Surrounding::afficher_surround()
{
    unsigned int size = radius * 2 + 1;
    for (unsigned int i = 0; i < size; i++)
    {
        for (unsigned int j = 0; j < size; j++)
        {
            if (this->interaction->at(i*size+j))
                cout<<"True ";
            else
                cout<<"False ";
        }
        cout << "\n";
    }
}

void Surrounding::addInteraction(vector<bool> _interactionLine){
    cout << "Adding " << _interactionLine.size() << "\n";
    for(unsigned int i = 0; i < _interactionLine.size() ; i++){
        this->interaction->push_back(_interactionLine.at(i));
    }
}
