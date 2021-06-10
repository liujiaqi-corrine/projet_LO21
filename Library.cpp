#include "Library.h"


Library::Library(){

    //Creation Voisinages
    listSurrounding.push_back(createSurroundingMoore());
    listSurrounding.push_back(createSurroundingVonNeumann());

    //Creation Modele de base
    listModels.push_back(createLifeGame());
    listModels.push_back(createBrianSBrain());

    currentModel=listModels[0];

}

void Library::addModel(QString nom, int nb){

    listModels.push_back(new Model(nom,nb));
    //return listModels[listModels.size()-1]; //Renvoi du dernier Modele ajouté

}

void Library::addSurrounding(int _diametre, QString _name){

    listSurrounding.push_back(new Surrounding(_diametre, _name));
}


Model* Library::createLifeGame(){

    Model* lifeGame = new Model("Life Game", 2);

    //Ajout des Etats
    lifeGame->getListStates()[0] = new State(0,QColor(Qt::black),"mort");
    lifeGame->getListStates()[1] = new State(1,QColor(Qt::white),"vivant");

    //Definition du voisinage
    lifeGame->setVoisinage(listSurrounding[0]);

    //Definition Regles
    lifeGame->setRule(new Rule_Intension("Regles LifeGame",lifeGame,2));
        //Pour l'etat mort
        lifeGame->getRule()->setVoisins(0,1,1,3,3);
        lifeGame->getRule()->setVoisins(1,1,1,2,3);
        lifeGame->getRule()->setVoisins(1,0,1,0,1);
        lifeGame->getRule()->setVoisins(1,0,1,4,1000);

    return lifeGame;
}

Model* Library::createBrianSBrain(){

    Model* briansbrain = new Model("Brian's Brain", 3);

    //Ajout des Etats
    briansbrain->getListStates()[0] = new State(0,QColor(Qt::green),"Zepos");
    briansbrain->getListStates()[1] = new State(1,QColor(Qt::red),"excite");
    briansbrain->getListStates()[2] = new State(2,QColor(Qt::yellow),"refractaire");

    //Definition du voisinage
    briansbrain->setVoisinage(listSurrounding[0]);

    //Definition Regles
    briansbrain->setRule(new Rule_Intension("Regles Brian's Brain",briansbrain,3));
        briansbrain->getRule()->setVoisins(0,1,1,2,2);
        briansbrain->getRule()->setVoisins(1,2,0,0,1000);
        briansbrain->getRule()->setVoisins(2,0,0,0,1000);

    return briansbrain;
}

Surrounding* Library::createSurroundingMoore(){

    Surrounding* voisins = new Surrounding(3,"Moore");
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            if (!(i==1 && j==1)) voisins->setInteractable(i,j,1);

    return voisins;

}

Surrounding* Library::createSurroundingVonNeumann(){

    Surrounding* voisins = new Surrounding(3,"Von Neumann");

    voisins->setInteractable(0,1,1); //Nord
    voisins->setInteractable(1,0,1); //Ouest
    voisins->setInteractable(1,2,1); //Est
    voisins->setInteractable(2,1,1); //Sud

    return voisins;
}
