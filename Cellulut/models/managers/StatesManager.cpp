#include "StatesManager.h"

#include <QSqlQuery>
#include <QSqlRecord>

StatesManager::StatesManager(DatabaseManager *databaseManager) : databaseManager(databaseManager)
{
    qInfo() <<  "StatesManager::StatesManager - constructor OK";
}

vector<State*>* StatesManager::findAllStatesByModelID(int modelID) {
    qInfo() <<  "StatesManager::findAllStatesByModelID()";

    QSqlQuery query(this->databaseManager->getDb());
    query.prepare("SELECT * FROM states where model_id = (:model_id)");
    query.bindValue(":model_id", modelID);
    query.exec();

    int colID = query.record().indexOf("id");
    int colColor = query.record().indexOf("color");
    int colLabel = query.record().indexOf("label");

    vector<State*>* result = new vector<State*>();

    while (query.next())
    {
        int id = query.value(colID).toInt();
        std::string color = query.value(colColor).toString().toStdString();
        std::string label = query.value(colLabel).toString().toStdString();

        State *model = new State(id,color,label);
        result->push_back(model);
    }

    return result;
}
