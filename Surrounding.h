#ifndef SURROUNDING_H_INCLUDED
#define SURROUNDING_H_INCLUDED

#include "State.h"
#include <QObject>

class Surrounding : public QObject
{
    protected :
        QString name;
        State* Model; // Voisinage d'un Model
        int diametre;
        int* interactable; //Pas de <vector> car on changera pas la taille

    public :
        Surrounding(int _diametre, QString name);
        //~Surrounding(); // error :undefined reference to vtable for : à cause d'une methode virtuelle
        QString getName() {return name;}
        int* getInteractable() const {return interactable;}
        void setInteractable(int row, int colomn, int index);
        void setNotInteractable(int row, int colomn, int index);
        int getDiametre() const {return diametre;}


        //Surcharge opérateur =  pour le calcul des regles ou surcharge de la classe grille
        //Stratégie fonction d'évolution : comparer les voisinages avec les regles et voir si une correspond, si oui on applique la regle
};


#endif // SURROUNDING_H_INCLUDED