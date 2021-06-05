#include "ModelsManager.h"

#include <QSqlQuery>
#include <QSqlRecord>

ModelsManager::ModelsManager(DatabaseManager *databaseManager) : databaseManager(databaseManager)
{
    qInfo() <<  "ModelsManager::ModelsManager - constructor OK";
}

vector<Model*>* ModelsManager::findAllModels()
{
    qInfo() <<  "ModelsManager::findAllModels()";

    QSqlQuery query("SELECT * FROM models", this->databaseManager->getDb() );

    int colID = query.record().indexOf("id");
    int colTitle = query.record().indexOf("title");
    int colDescription = query.record().indexOf("title");
    int colAuthor = query.record().indexOf("author");
    int colDateOfCreation = query.record().indexOf("dateOfCreation");

    vector<Model*>* result = new vector<Model*>();

    while (query.next())
    {
        int id = query.value(colID).toInt();
        std::string title = query.value(colTitle).toString().toStdString();
        std::string description = query.value(colDescription).toString().toStdString();
        std::string author = query.value(colAuthor).toString().toStdString();
        std::string dateOfCreation = query.value(colDateOfCreation).toString().toStdString();

        Model *model = new Model(id,title,description,author,dateOfCreation);
        result->push_back(model);
    }

    return result;
}
