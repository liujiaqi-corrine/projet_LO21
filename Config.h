#ifndef CONFIG_H
#define CONFIG_H

#include "State.h"
#include "Cell.h"
#include <vector>
#include <QTableWidgetItem>

class Config {

    private:
        int diametre;
        int nbCellule;
        int* environment;
        int suivant;

    public:
        Config(int _diametre, int _suivant) {

            diametre = _diametre;
            nbCellule = diametre*diametre;
            environment = new int[nbCellule];
            suivant = _suivant;

            for (int i=0; i<diametre; i++)
                for(int j=0; j<diametre; j++)
                    environment[diametre*i+j]=-1;

        };

    public slots:
        //void setEnvironment(int _x, int _y, int _index) {environment[diametre*_x+_y]= _index;}
        void setEnvironment(int _x, int _y, int _index) {environment[diametre*_x+_y]= _index;}
        //void setEnvironment(Cell *item) {environment[diametre*item->getX()+item->getY()]= item->getState()->getIndex();}
        int* getEnvironment() {return environment;}
        int getSuivant() {return suivant;}

};

// Une config est construite de cette façon :
// grâce à l'indice du config* de rule_extension on connait l'état de départ
// l'attribut suivant determine l'état de transformation si la config est respecté
// l'environnement represente la config avec les indices qui designe les états (-1 si la case n'est pas prise en compte)




#endif // CONFIG_H
