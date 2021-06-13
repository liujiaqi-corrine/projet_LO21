#include "DatabaseManager.h"
#include "main.h"
DatabaseManager::DatabaseManager(const QString &path)
{
    this->db = QSqlDatabase::addDatabase("QSQLITE");
    this->db.setDatabaseName(path);

    if (!this->db.open())
    {
        qWarning() << "DatabaseManager::DatabaseManager - ERROR: connection with database fail";
    }
    else
    {
        qInfo() << "DatabaseManager::DatabaseManager - database connection ok";
    }
}
