#include "databasehandler.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

QSqlDatabase db;

/*!
 * \brief DatabaseHandler::DatabaseHandler Constructor for the DatabaseHandler
 */
DatabaseHandler::DatabaseHandler()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("../src/OMBI.db");
    //!print an error if connection to db fails
    if (!db.open())
    {

    }
    else{}

}

/*!
 * \brief DatabaseHandler::getAll Method to get all values in a SQL table
 * \param table
 * \return
 */
QSqlQuery DatabaseHandler::getAll(std::string table)
{
    QSqlQuery query(db);
    //!get all values from the database
    QString statement = "SELECT * FROM "+QString::fromStdString(table)+";";
    query.prepare(statement);
    if(!query.exec())
    {

    }
    else
    {

    }
    return query;

}

/*!
 * \brief DatabaseHandler::searchForValue Method to retrieve a specific value or set of values based a user provided query
 * \param table
 * \param columnWant
 * \param columnHave
 * \param dataHave
 * \return
 */
QSqlQuery DatabaseHandler::searchForValue(string table,string columnWant,string columnHave,string dataHave)
{
    QSqlQuery query(db);
    //!get all values from the database
    string statement = "SELECT "+columnWant+" FROM "+table+" WHERE "+columnHave+"='"+dataHave+"';";
    query.prepare(QString::fromStdString(statement));
    if(!query.exec())
    {

    }
    else
    {

    }

    return query;
}

/*!
 * \brief DatabaseHandler::searchForRegEx A method to retrieve values from a table based on a regular expressions search
 * \param table
 * \param columnWant
 * \param columnHave
 * \param dataHave
 * \return
 */
QSqlQuery DatabaseHandler::searchForRegEx(string table,string columnWant,string columnHave,string dataHave)
{
    QSqlQuery query(db);
    //!get all values from the database
    string statement = "SELECT "+columnWant+" FROM "+table+" WHERE "+columnHave+" like '"+dataHave+"';";
    query.prepare(QString::fromStdString(statement));
    if(!query.exec())
    {

    }
    else
    {

    }

    return query;
}

/*!
 * \brief DatabaseHandler::searchForGraphable A method that searched for values based on three search parameters, intended for searching when city,year,subservice selected
 * \param table
 * \param columnWant
 * \param columnHave1
 * \param dataHave1
 * \param columnHave2
 * \param dataHave2
 * \param columnHave3
 * \param dataHave3
 * \return
 */
QSqlQuery DatabaseHandler::searchForGraphable(string table,string columnWant,string columnHave1,string dataHave1,string columnHave2,string dataHave2,string columnHave3,string dataHave3)
{
    QSqlQuery query(db);
    //!get all values from the database
    string statement = "SELECT "+columnWant+" FROM "+table+" WHERE "+columnHave1+" IN ('"+dataHave1+"') AND "+columnHave2+" IN ('"+dataHave2+"') AND "+columnHave3+" IN ('"+dataHave3+"');";
    query.prepare(QString::fromStdString(statement));
    if(!query.exec())
    {

    }
    else
    {

    }


    return query;
}

/*!
 * \brief DatabaseHandler::searchForNonRepeating Method that retrieves all values from a column or columns but discards any duplicate data
 * \param table
 * \param columnWant
 * \return
 */
QSqlQuery DatabaseHandler::searchForNonRepeating(string table,string columnWant)
{
    QSqlQuery query(db);
    //!get all values from the database
    string statement = "SELECT "+columnWant+" FROM "+table+" GROUP BY "+columnWant+";";
    query.prepare(QString::fromStdString(statement));
    if(!query.exec())
    {

    }
    else
    {

    }

    return query;
}
