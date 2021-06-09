#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>

class DatabaseManager
{
private:
    QSqlDatabase db;
public:
    DatabaseManager(const QString &path);
    QSqlDatabase getDb() const {return this->db;}
};

#endif // DATABASEMANAGER_H
