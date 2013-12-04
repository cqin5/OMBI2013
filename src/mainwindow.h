/*!
 * Authors: Vietca Vo, Fraser Filice, Chuhan Qin, Stephan De Jegar, Sohrab Dolatabadi, Group 6
 * Description: This is the main window which is responsible for creating the graph,
 * data passed to main window through the stub and are used for plotting
 * Date: October 25, 2013
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "qcustomplot.h"
#include "QFileDialog"
#include "QMessageBox"
#include "chartcolor.h"
#include <iostream>
#include <fstream>
#include <QSqlDriver>
#include <QSqlQuery>
#include "get_started.h"

#include <QApplication>
#include <QMenu>
#include <QMenuBar>


#include "datasearch.h"

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    double current;
    ~MainWindow();


private slots:
    //! When "Get Graph" button is clicked, this slot is triggered.
//    void slot_get_graph(bool);

   // void on_MainWindow_customContextMenuRequested(const QPoint &pos);

    void slot_save_to_image();

    //void slot_toCSV();

//    void on_graphBtn_clicked();

//    void on_tableBtn_clicked();

//    void on_settingsBtn_clicked();
//    void on_comboBox_currentIndexChanged(const QString &arg1);

//    void on_lineGraphBtn_clicked();

    void DataToTable(QSqlQuery query);

    //void DataToCSV(QSqlQuery query, QString fileName);
    void slot_refresh_sub();
    void slot_search();
    QVector< QVector< QVector<double> > > DataToVectors(QSqlQuery query);
    void DataToGraph(QVector< QVector< QVector<double> > > cities);

    //! Menu
    void get_started_info();
    void about_info();
    void welcome_screen();

    //! Buttons
    void on_button_bar_graph_clicked();
    //! table view buttons
    void on_button_table_view_clicked();

    //! selection view buttons
    void on_button_menu_clicked();


    //!line graph view buttons
    void on_button_line_graph_clicked();

    void on_continue_button_clicked();

    void on_Button_csv_clicked();
    void on_Button_clear_all_clicked();



private:
    Ui::MainWindow *ui;
    void showList();
    QList<QString> *returned_list;
    QList<QString> *returned_listRef;
    DataSearch *ds;
    QSqlQuery query;
    //! Create the menu classes
    void createActions();
    void createMenus();
    //! Menu Items
    QMenu   *home;
    QMenu   *help;
    QAction *welcome;
    QAction *exit;
    QAction *start;
    QAction *about;
    get_started *quickstart;
};

#endif // MAINWINDOW_H
