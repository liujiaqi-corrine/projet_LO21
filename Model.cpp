#include "Model.h"

Model::Model(QString _name, int _nbState)
{
    name = _name;
    nbState = _nbState;

    listStates= new State*[nbState];
    voisinage= nullptr;

    //listStates[0] = new State(0, QColor(Qt::blue));
    //listStates[1] = new State(1, QColor(Qt::red));

    //grid = new Grid();

}

Model::Model(){

    name="";
    nbState=2;

    listStates= new State*[nbState];
    voisinage = nullptr;

    listStates[0]= new State(0, QColor(Qt::white));
    listStates[1] = new State(1, QColor(Qt::black));

}

QString Model::getName() const{return name;}

int Model::getNbState() const{return nbState;}

State** Model::getListStates() const{return listStates;}

//Grid* Model::getGrid() const{return grid;}

void Model::setName(QString _name){name = _name;}





