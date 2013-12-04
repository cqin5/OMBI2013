#ifndef DATASEARCH_H
#define DATASEARCH_H

#include <QList>
#include <QString>
#include <iostream>
#include <fstream>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QtCore/QCoreApplication>
#include <QtSql/QSqlDatabase>

#include "databasehandler.h"


class DataSearch
{
public:
    DataSearch();
    QList<QString> getCities();
    QList<QString> getYears();
    QList<QString> getServices();
    QList<QString> getSubDirectory(QString service);
    QList<QString> getSubDirectoryRef(QString service);
    QSqlQuery searchForGraphable(std::string table,std::string columnWant,std::string columnHave1,std::string dataHave1,std::string columnHave2,std::string dataHave2,std::string columnHave3,std::string dataHave3);

private:
    DatabaseHandler *db;
    QList<QString> DataToQList(QSqlQuery query);
};

#endif // DATASEARCH_H
