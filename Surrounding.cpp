#include "Surrounding.h"

Surrounding::Surrounding(int _diametre, QString _name) : QObject() {

    name = _name;
    diametre = _diametre;
    interactable = new int[diametre*diametre];

    //Initialisation du voisinage à : aucun voisin
    for (int i=0; i<diametre; i++)
        for(int j=0; j<diametre; j++)
            interactable[diametre*i+j]=0;

}

void Surrounding::setInteractable(int row, int colomn, int index){

    interactable[diametre*row+colomn]=index;

}

