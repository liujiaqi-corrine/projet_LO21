#include "Surrounding.h"

Surrounding::Surrounding(int _diametre) : QObject() {

    diametre = _diametre;
    nbVoisins = diametre*diametre;
    interactable = new bool[nbVoisins];

    //Initialisation du voisinage à : aucun voisin
    for (int i=0; i<diametre; i++)
        for(int j=0; j<diametre; j++)
            interactable[diametre*i+j]=false;

}

void Surrounding::setInteractable(int row, int colomn){

    interactable[diametre*row+colomn]=true;

}
