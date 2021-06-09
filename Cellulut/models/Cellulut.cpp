#include "Cellulut.h"

Cellulut::Cellulut()
{
    DatabaseManager *databaseManager = new DatabaseManager("../Cellulut/cellulut.db");
    this->statesManager = new StatesManager(databaseManager);
    this->modelsManager = new ModelsManager(databaseManager);

    qInfo() <<  "Cellulut::Cellulut - constructor OK";
}

Cellulut::~Cellulut()
{
    delete this->statesManager;
    delete this->modelsManager;
}

void Cellulut::init(){
    qInfo() << "Cellulut::init()";

    this->initListOfModels();
}

void Cellulut::initListOfModels(){
    qInfo() << "Cellulut::init()";

    this->listOfModels = this->modelsManager->findAllModels();
    for(unsigned int i = 0; i < this->listOfModels->size(); i++){
        Model *model = this->listOfModels->at(i);
        vector<State*> *listOfStates = this->statesManager->findAllStatesByModelID(model->getId());
        model->setListStates(listOfStates);
    }
}
