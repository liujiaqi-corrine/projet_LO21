#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include "Model.h"
#include <vector>

class Library
{
    protected :
        std::vector<Model*> listModels ;
        std::vector<Surrounding*> listSurrounding;
        Model* currentModel;

        Model* createLifeGame();
        Model* createBrianSBrain();
        Surrounding* createSurroundingMoore();
        Surrounding* createSurroundingVonNeumann();

    public :
        Library();
        std::vector<Model*> getListModels() const {return listModels;}
        std::vector<Surrounding*> getListSurrounding() const {return listSurrounding;}
        void addModel(QString nom, int nb);
        void addSurrounding(int _diametre, QString _name);
        Model* getCurrentModel() {return currentModel;}
        void setCurrentModel(int indice) {currentModel = listModels[indice];}



};


#endif // LIBRARY_H_INCLUDED
