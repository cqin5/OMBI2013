#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <iostream>
#include <fstream>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QtCore/QCoreApplication>
#include <QtSql/QSqlDatabase>
#include <QVariant>
#include <QtGui>

class DatabaseHandler
{
public:
    DatabaseHandler();

    QSqlQuery getAll(std::string table);
    QSqlQuery searchForValue(std::string table, std::string columnWant, std::string columnHave, std::string dataHave);
    //QSqlQuery searchNExport(std::string table,std::string columnHave,std::string columnWant,std::string dataHave,std::string fileName);
    QSqlQuery searchForNonRepeating(std::string table,std::string columnWant);
    QSqlQuery searchForGraphable(std::string table,std::string columnWant,std::string columnHave1,std::string dataHave1,std::string columnHave2,std::string dataHave2,std::string columnHave3,std::string dataHave3);
    QSqlQuery searchForRegEx(std::string table,std::string columnWant,std::string columnHave,std::string dataHave);
};

#endif // DATABASEHANDLER_H
