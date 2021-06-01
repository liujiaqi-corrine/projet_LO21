#include "Library.h"


Library::Library(){


    //Creation Modele de base
    listModels.push_back(createLifeGame());
    listModels.push_back(createBrianSBrain());

    currentModel=listModels[1];

}

void Library::addModel(QString nom, int nb){

    listModels.push_back(new Model(nom,nb));
    //return listModels[listModels.size()-1]; //Renvoi du dernier Modele ajouté

}


Model* Library::createLifeGame(){

    Model* lifeGame = new Model("Life Game", 2);

    //Ajout des Etats
    lifeGame->getListStates()[0] = new State(0,QColor(Qt::black),"mort");
    lifeGame->getListStates()[1] = new State(1,QColor(Qt::white),"vivant");

    //Definition du voisinage
    lifeGame->setVoisinage(3);
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            if (i!=j) lifeGame->getVoisinage()->setInteractable(i,j);

    //Definition Regles

    return lifeGame;
}

Model* Library::createBrianSBrain(){

    Model* briansbrain = new Model("Brian's Brain", 3);

    //Ajout des Etats
    briansbrain->getListStates()[0] = new State(0,QColor(Qt::green),"Zepos");
    briansbrain->getListStates()[1] = new State(1,QColor(Qt::red),"excité");
    briansbrain->getListStates()[2] = new State(2,QColor(Qt::yellow),"réfractaire");

    //Definition du voisinage
    briansbrain->setVoisinage(3);
    briansbrain->getVoisinage()->setInteractable(0,1); //Nord
    briansbrain->getVoisinage()->setInteractable(1,0); //Ouest
    briansbrain->getVoisinage()->setInteractable(1,2); //Est
    briansbrain->getVoisinage()->setInteractable(2,1); //Sud

    //Definition Regles

    return briansbrain;
}

