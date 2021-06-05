#ifndef CELLULUT_H
#define CELLULUT_H

#include "models/managers/ModelsManager.h"
#include "models/managers/StatesManager.h"

class Cellulut
{
private:
    ModelsManager* modelsManager;
    StatesManager* statesManager;
    vector<Model*>* listOfModels;

    void initListOfModels();
public:
    Cellulut();
    ~Cellulut();

    vector<Model*>* getListOfModels() const{ return this->listOfModels;}

    void init();
};

#endif // CELLULUT_H
