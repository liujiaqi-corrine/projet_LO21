#ifndef LIBRARY_H_INCLUDED
#define LIBRARY_H_INCLUDED

#include "Model.h"
#include <vector>

class Library
{
    protected :
        std::vector<Model*> listModels ;
        Model* currentModel;

        Model* createLifeGame();
        Model* createBrianSBrain();

    public :
        Library();
        std::vector<Model*> getListModels() const {return listModels;}
        void addModel(QString nom, int nb);
        Model* getCurrentModel() {return currentModel;}
        void setCurrentModel(int indice) {currentModel = listModels[indice];}



};


#endif // LIBRARY_H_INCLUDED
