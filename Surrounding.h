#ifndef SURROUNDING_H_INCLUDED
#define SURROUNDING_H_INCLUDED

#include "State.h"
#include <QObject>

class Surrounding : public QObject
{
    protected :
        State* Model; // Voisinage d'un Model
        int diametre;
        bool* interactable; //Pas de <vector> car on changera pas la taille
        int nbVoisins;

    public :
        Surrounding(int _diametre);
        //~Surrounding(); // error :undefined reference to vtable for
        bool* getInteractable() const {return interactable;}
        void setInteractable(int i, int j);
        int getDiametre() const {return diametre;}
};


#endif // SURROUNDING_H_INCLUDED
