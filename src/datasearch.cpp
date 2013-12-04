#include "datasearch.h"

/*!
 * \brief DataSearch::DataSearch constructor for the data search class
 */
DataSearch::DataSearch()
{
    db = new DatabaseHandler();
}

/*!
 * \brief DataSearch::getCities method that query's database handler for a list of all cities without repeats and passes the response as a QList
 * \return
 */
QList<QString> DataSearch::getCities(){
    return DataToQList(db->searchForNonRepeating("MeasureData","Municipality"));

}

/*!
 * \brief DataSearch::getYears method that query's database handler for a list of all years without repeats and passes the response as a QList
 * \return
 */
QList<QString> DataSearch::getYears(){
    return DataToQList(db->searchForNonRepeating("MeasureData","Year"));;
}

/*!
 * \brief DataSearch::getServices method to create a QList of human readable services
 * \return
 */
QList<QString> DataSearch::getServices(){
    QList<QString> *services = new QList<QString>();
    services->append("Fire");
    services->append("Libraries");
    services->append("Parks");
    services->append("Police");
    services->append("Waste Management");
    services->append("Water");

    return *services;
}

/*!
 * \brief DataSearch::getSubDirectory method to get a QList of all human readable subservices given a service
 * \param service
 * \return
 */
QList<QString> DataSearch::getSubDirectory(QString service){
    return DataToQList(db->searchForRegEx("Measures","Title","MeasureID",service.toStdString()));
}

/*!
 * \brief DataSearch::getSubDirectoryRef method to get a QList of all unique identifiers for subservices given a service
 * \param service
 * \return
 */
QList<QString> DataSearch::getSubDirectoryRef(QString service){
    return DataToQList(db->searchForRegEx("Measures","MeasureID","MeasureID",service.toStdString()));
}

/*!
 * \brief DataSearch::searchForGraphable A method that searched for values based on three search parameters, intended for searching when city,year,subservice selected
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
QSqlQuery DataSearch::searchForGraphable(std::string table,std::string columnWant,std::string columnHave1,std::string dataHave1,std::string columnHave2,std::string dataHave2,std::string columnHave3,std::string dataHave3)
{
    return db->searchForGraphable(table,columnWant,columnHave1,dataHave1,columnHave2,dataHave2,columnHave3,dataHave3);
}

/*!
 * \brief DataSearch::DataToQList method that takes a given QSqlQuery response and parses the data into a QList
 * \param query
 * \return
 */
QList<QString> DataSearch::DataToQList(QSqlQuery query)
{
    QList<QString> output;
    //!search through all data in the sql database and assign each returned entry to a table entry

         while (query.next())
         {
             int i = 0;
             for(i = 0;query.value(i).isValid();++i)
             {
                 output.push_back(query.value(i).toString());
             }


         }
         return output;
}
