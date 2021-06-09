#ifndef STATESMANAGER_H
#define STATESMANAGER_H

#include "models/managers/DatabaseManager.h"
#include "models/State.h"

class StatesManager
{
private:
    DatabaseManager *databaseManager;
public:
    StatesManager(DatabaseManager *databaseManager);

    vector<State*>* findAllStatesByModelID(int modelID);
};

#endif // STATESMANAGER_H
