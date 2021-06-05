#ifndef MODELSMANAGER_H
#define MODELSMANAGER_H

#include "models/managers/DatabaseManager.h"
#include "models/Model.h"

class ModelsManager
{
private:
    DatabaseManager *databaseManager;
public:
    ModelsManager(DatabaseManager *databaseManager);

    vector<Model*>* findAllModels();
};

#endif // MODELSMANAGER_H
