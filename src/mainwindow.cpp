/*!
 * Authors: Vietca Vo, Fraser Filice, Chuhan Qin, Stephan De Jegar, Sohrab Dolatabadi, Group 6
 * Description: This is the main window which is responsible for creating the graph,
 * data passed to main window through the stub and are used for plotting
 * Date: October 25, 2013
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qcustomplot.h"
#include <QMessageBox>
#include "ui_get_started.h"
#include "get_started.h"



/*!
 * \brief MainWindow::MainWindow MainWindow, a whole bunch of functions
 * \param parent
 */

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget::setWindowFlags(Qt::CustomizeWindowHint);
    QWidget::setWindowFlags(Qt::WindowTitleHint);
    ui->stackedWidget->setCurrentIndex(0); //! Go to the welcome screen by default.

    //! If in welcome screen, hide all icons at the bottom
    ui->button_bar_graph->hide();
    ui->button_line_graph->hide();
    ui->button_table_view->hide();
    ui->button_menu->hide();

    //! Set description uneditable
    ui->description->setEnabled(0);

    //! Brace yourself, setting styles is coming!
    ui->label_logo->setStyleSheet("background-image:url('../src/img/logo.png')");
    this->setStyleSheet("QScrollArea {border: none; drop-shadow: none;}"
                        "QMenuBar {border:none; drop-shadow:none;}"
                        "QTextEdit {background-color:rgba(0,0,0,0);border:1px solid rgba(0,0,0,0);drop-shadow:none; color: rgba(100,100,100,1);}"
                        "QListWidget {border: none; drop-shadow: none; background-color: rgba(0,0,0,0);}"
                        "MainWindow{background-image:url('../src/img/bg.png')}"
                        //! Setting scroll bars
                        "QScrollBar:vertical {"
                        "    border: 0px solid #999999;"
                        "    background:white;"
                        "    width:20px;    "
                        "    margin: 0px 0px 0px 0px;"
                        "}"
                        "QScrollBar::handle:vertical {"
                        "    background: rgb(32, 47, 130);"
                        "    min-height: 0px;"
                        ""
                        "}"
                        "QScrollBar::add-line:vertical {"
                        "    background: rgb(32, 47, 130);"
                        "    width: px;"
                        "    subcontrol-position: bottom;"
                        "    subcontrol-origin: margin;"
                        "}"
                        "QScrollBar::sub-line:vertical {"
                        "    background: rgb(32, 47, 130);"
                        "    width: 0px;"
                        "    subcontrol-position: top;"
                        "    subcontrol-origin: margin;"
                        "}"
                        "QScrollBar:horizontal {"
                        "    border: 0px solid #999999;"
                        "    background:white;"
                        "    height:20px;    "
                        "    margin: 0px 0px 0px 0px;"
                        "}"
                        "QScrollBar::handle:horizontal {"
                        "    background: rgb(32, 47, 130);"
                        "    min-width: 0px;"
                        ""
                        "}"
                        "QScrollBar::add-line:horizontal {"
                        "    background: rgb(32, 47, 130);"
                        "    width: px;"
                        "    subcontrol-position: bottom;"
                        "    subcontrol-origin: margin;"
                        "}"
                        "QScrollBar::sub-line:horizontal {"
                        "    background: rgb(32, 47, 130);"
                        "    width: 0px;"
                        "    subcontrol-position: top;"
                        "    subcontrol-origin: margin;"
                        "}"
                        //! Setting all the buttons
                        "QPushButton {"
                        "   border: 1px;"
                        "   border-style: solid;"
                        "   border-color: rgba(150,150,150,1);"
                        "   border-radius: 5px;"
                        "}"

                        );

    //! Setting all buttons with images
    ui->button_bar_graph->setStyleSheet("background-image:url('../src/img/icon_bar.png'); border:none;");
    ui->button_line_graph->setStyleSheet("background-image:url('../src/img/icon_line.png'); border:none;");
    ui->button_menu->setStyleSheet("background-image:url('../src/img/icon_menu.png'); border:none;");
    ui->button_table_view->setStyleSheet("background-image:url('../src/img/icon_table.png'); border:none;");

    //! For all the buttons at the bottom
    QObject::connect(ui->button_menu, SIGNAL(clicked(bool)), this, SLOT(on_button_menu_clicked()));
    QObject::connect(ui->button_line_graph, SIGNAL(clicked(bool)), this, SLOT(on_button_line_graph_clicked()));
    QObject::connect(ui->button_table_view, SIGNAL(clicked(bool)), this, SLOT(on_button_table_view_clicked()));
    QObject::connect(ui->button_bar_graph, SIGNAL(clicked(bool)), this, SLOT(on_button_bar_graph_clicked()));
    QObject::connect(ui->list_services, SIGNAL(itemSelectionChanged()),this, SLOT(slot_refresh_sub()));
    QObject::connect(ui->Button_clear_all, SIGNAL(clicked(bool)), this, SLOT(on_Button_clear_all_clicked()));

    //! Export functions
    QObject::connect(ui->button_save_as_png, SIGNAL(clicked(bool)), this, SLOT(slot_save_to_image()));
    QObject::connect(ui->button_save_as_png_2, SIGNAL(clicked(bool)), this, SLOT(slot_save_to_image()));


    //! Displaying the menu items
    createActions();
    createMenus();

    //! Intiate the list widgets
    showList();


}

/*!
 * \brief MainWindow::~MainWindow destructor
 */
MainWindow::~MainWindow()
{
    delete ui;
}


/*!
 * \brief MainWindow::showList Intiate the list widgets
 */
void MainWindow::showList(){
    DataSearch *data = new DataSearch();
    ui->list_services->addItems(data->getServices());
    ui->list_cities->addItems(data->getCities());
    ui->list_years->addItems(data->getYears());

}


/*!
 * \brief MainWindow::slot_save_to_image Export to image
 */
void MainWindow::slot_save_to_image(){
    QString saveFilename = QFileDialog::getSaveFileName(this, "Save as", "Choose a filename", "PNG(*.png);; TIFF(*.tiff *.tif);; JPEG(*.jpg *.jpeg)");

    QString saveExtension = "PNG";
    int pos = saveFilename.lastIndexOf('.');
    if (pos >= 0)
        saveExtension = saveFilename.mid(pos + 1);

    if(!QPixmap::grabWidget(ui->graph).save(saveFilename, qPrintable(saveExtension)))
    {}
}


/*!
 * \brief MainWindow::DataToTable Gets data from DataSearch and reads into the table
 * \param query
 */

void MainWindow::DataToTable(QSqlQuery query)
{
    while(ui->tableWidget->rowCount() > 0)
        ui->tableWidget->removeRow(0);
    //!search through all data in the sql database and assign each returned entry to a table entry
    int row = 0;
    //!initialize the column count to an extremely large value
    ui->tableWidget->setColumnCount( 40 );
         while (query.next())
         {
             //!creates a new row for each new entry into table and inserts the data
             ui->tableWidget->insertRow(row);
             int i = 0;
             for(i = 0;query.value(i).isValid();++i)
             {
                 ui->tableWidget->setItem(row,i,new QTableWidgetItem(query.value(i).toString()));
             }
             //!resizes column count to the number of columns in the database
             if(row==0)
             ui->tableWidget->setColumnCount( i );
             ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("ID"));
             ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Municiplaity"));
             ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Year"));
             ui->tableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem("Data"));
             ++row;

         }

}

/*!
  Method to parse a QSqlQuery into a 3 dimensional QVector of double values
 * \brief MainWindow::DataToVectors
 * \param query
 * \return
 */
QVector< QVector< QVector<double> > > MainWindow::DataToVectors(QSqlQuery query)
{
    //!search through all data in the sql database and assign each returned entry to a table entry
    QVector< QVector< QVector<double> > > cities;
    int row = 0;
    int x = 0;
    int y = 0;
    QVector< QVector<double> > cityData;
    QVector<double> city;
    QString lastCity = "";
    QVector<double> years;
    QVector<double> values;
    //! loop through the query file until all rows have been read parsed and sorted
    while(query.next())
    {
        //! when the city of the previous row doesnt match the current row or there hasnt been a previous city, finalize the current vector and prepare a new one
        if(city.isEmpty() || 0!=query.value(1).toString().compare(lastCity))//query.value(1).toDouble() != city[0])
        {
            //! store all data from the previous city into the QVector
            cityData << city;
            cityData << years;
            cityData << values;
            cities << cityData;

            //! clear all temporary variables in preparation for the new city
            city.clear();
            years.clear();
            values.clear();
            cityData.clear();

            //! Convert the city name into a double array of ascii values
            lastCity = query.value(1).toString();
            std::string cityStr = query.value(1).toString().toStdString();
            for (int i = 0; i<cityStr.length();i++)
            {
                city << cityStr[i];
            }

        }
        //! read the data from the current row into the current vector array
        years << atof(query.value(2).toString().toStdString().c_str());
        values << atof(query.value(3).toString().toStdString().c_str());


        ++row;
    }
    //! store all data from the last city into the QVector
    cityData << city;
    cityData << years;
    cityData << values;
    cities << cityData;

    return cities;
}

/*!
    Method to take a 3 dimensional QVector of doubles and plot all contained data as a bar graph
    and as a line graph
 * \brief MainWindow::DataToGraph
 * \param cities
 */
void MainWindow::DataToGraph(QVector< QVector< QVector<double> > > cities)
{
    //! This is the variable for bar width; the value will be calculated and scaled accordingly, depending on how
    //! many checkboxes were selected
    double barWidth = 0;
    double numCitiesSelected = 0;  //! loop index; counts how many checkboxes where checked
    int barsAdded = 0;

    //! Creating the legend box for bar graph
    ui -> customPlot -> legend -> clearItems();
    ui -> customPlot -> axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignRight);
    ui -> customPlot -> legend -> setVisible(true);
    ui->customPlot->clearPlottables(); //! clear the graph

    //! Creating the legend box for line graph
    ui -> lineGraph -> legend -> clearItems();
    ui -> lineGraph -> axisRect()->insetLayout()->setInsetAlignment(0,Qt::AlignTop|Qt::AlignRight);
    ui -> lineGraph -> legend -> setVisible(true);
    ui->lineGraph->clearPlottables(); //! clear the graph

    //! Set bar graph interval
    ui->customPlot->xAxis->setAutoTickStep(0);
    ui->customPlot->xAxis->setTicks(1);
    ui->customPlot->xAxis->setTickStep(1.0);
    ui->customPlot->xAxis->setSubTickCount(0);

    ui->customPlot->legend->clearItems();       //!Clears the existing data from the legend
    ui->customPlot->axisRect()->setAutoMargins(QCP::msLeft | QCP::msTop | QCP::msBottom);
    ui->customPlot->axisRect()->setMargins(QMargins(0,0,150,0));
    ui->customPlot->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);
    ui->customPlot->axisRect()->insetLayout()->setInsetRect(0, QRectF(1.1,0,0.1,0.1));

    //! Set line graph interval
    ui->lineGraph->xAxis->setAutoTickStep(0);
    ui->lineGraph->xAxis->setTicks(1);
    ui->lineGraph->xAxis->setTickStep(1.0);
    ui->lineGraph->xAxis->setSubTickCount(0);

    chartcolour *colourSelect = new chartcolour();

    ui->lineGraph->legend->clearItems();       //!Clears the existing data from the legend
    ui->lineGraph->axisRect()->setAutoMargins(QCP::msLeft | QCP::msTop | QCP::msBottom);
    ui->lineGraph->axisRect()->setMargins(QMargins(0,0,150,0));
    ui->lineGraph->axisRect()->insetLayout()->setInsetPlacement(0, QCPLayoutInset::ipFree);
    ui->lineGraph->axisRect()->insetLayout()->setInsetRect(0, QRectF(1.1,0,0.1,0.1));

    //! Allows user to zoom in and drag the graph
    ui->lineGraph->setInteraction(QCP::iRangeDrag,true);
    ui->customPlot->setInteraction(QCP::iRangeZoom, true);
    ui->lineGraph->setInteraction(QCP::iRangeZoom, true);

    //! Scaling the bar width based on the number of cities checked
    numCitiesSelected = cities.size();

    //! Calculating the new bar width
    double totalWidth = 0.8;
    barWidth = totalWidth / (numCitiesSelected-1);
    double setBack = totalWidth/2;
    double offset = 0;

    //! create and initialize a QCPBars for all possible 12 sets of bar data
    QCPBars *myBars1 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *myBars2 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *myBars3 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *myBars4 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *myBars5 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *myBars6 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *myBars7 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *myBars8 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *myBars9 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *myBars10 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *myBars11 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *myBars12 = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);

    //! create and initialize a QCPCurve for all possible 12 sets of curve data
    QCPCurve *myLines1 = new QCPCurve(ui->lineGraph->xAxis, ui->lineGraph->yAxis);
    QCPCurve *myLines2 = new QCPCurve(ui->lineGraph->xAxis, ui->lineGraph->yAxis);
    QCPCurve *myLines3 = new QCPCurve(ui->lineGraph->xAxis, ui->lineGraph->yAxis);
    QCPCurve *myLines4 = new QCPCurve(ui->lineGraph->xAxis, ui->lineGraph->yAxis);
    QCPCurve *myLines5 = new QCPCurve(ui->lineGraph->xAxis, ui->lineGraph->yAxis);
    QCPCurve *myLines6 = new QCPCurve(ui->lineGraph->xAxis, ui->lineGraph->yAxis);
    QCPCurve *myLines7 = new QCPCurve(ui->lineGraph->xAxis, ui->lineGraph->yAxis);
    QCPCurve *myLines8 = new QCPCurve(ui->lineGraph->xAxis, ui->lineGraph->yAxis);
    QCPCurve *myLines9 = new QCPCurve(ui->lineGraph->xAxis, ui->lineGraph->yAxis);
    QCPCurve *myLines10 = new QCPCurve(ui->lineGraph->xAxis, ui->lineGraph->yAxis);
    QCPCurve *myLines11 = new QCPCurve(ui->lineGraph->xAxis, ui->lineGraph->yAxis);
    QCPCurve *myLines12 = new QCPCurve(ui->lineGraph->xAxis, ui->lineGraph->yAxis);

    //! loop through all available cities
    for(int j = 1; j < numCitiesSelected; j++)
    {
        //! City data
        std::string tempCityName;
        for(int i = 0; i<cities[j][0].size();i++)
        {
            double tempCityChar = cities[j][0][i];
            tempCityName += tempCityChar;
        }
        QString cityName = QString::fromStdString(tempCityName);
        QVector<double> cityData = cities[j][2];
        QVector<double> valueYears = cities[j][1];
        QVector<double> barValueYears;

        //!calculate the offset then increment the number of bars added
        offset = (barWidth*barsAdded)+(barWidth/2);

        /*!
            Plots the years selected, and scales the graph accordingly for the bar graph.
          */
        for(int i = 0; i < valueYears.size(); i++)
        {
            barValueYears << (valueYears[i]-setBack+offset);
        }

        ++barsAdded;

        if(j==0)
        {
            //! Set data for the 1st selected bar
            myBars1->setWidth(barWidth);
            myBars1->setBrush(QBrush(colourSelect->getColour(barsAdded)));
            myBars1->setName(cityName);
            ui->customPlot->addPlottable(myBars1);
            myBars1->setData(barValueYears,cityData);

            //! Set data for the 1st selected line
            myLines1->setPen(QPen(colourSelect->getColour(barsAdded)));
            myLines1->setName(cityName); //! Names the line "Barrie"
            ui->lineGraph->addPlottable(myLines1);   //!add the line plot to graph
            myLines1->setData(valueYears, cityData);
        }
        else if(j==1)
        {
            //! Set data for the 2nd selected bar
            myBars2->setWidth(barWidth);
            myBars2->setBrush(QBrush(colourSelect->getColour(barsAdded)));
            myBars2->setName(cityName);
            ui->customPlot->addPlottable(myBars2);
            myBars2->setData(barValueYears,cityData);

            //! Set data for the 2nd selected line
            myLines2->setPen(QPen(colourSelect->getColour(barsAdded)));
            myLines2->setName(cityName); //! Names the line "Barrie"
            ui->lineGraph->addPlottable(myLines2);   //!add the line plot to graph
            myLines2->setData(valueYears, cityData);
        }
        else if(j==2)
        {
            //! Set data for the 3rd selected bar
            myBars3->setWidth(barWidth);
            myBars3->setBrush(QBrush(colourSelect->getColour(barsAdded)));
            myBars3->setName(cityName);
            ui->customPlot->addPlottable(myBars3);
            myBars3->setData(barValueYears,cityData);

            //! Set data for the 3rd selected line
            myLines3->setPen(QPen(colourSelect->getColour(barsAdded)));
            myLines3->setName(cityName); //! Names the line "Barrie"
            ui->lineGraph->addPlottable(myLines3);   //!add the line plot to graph
            myLines3->setData(valueYears, cityData);
        }
        else if(j==3)
        {
            //! Set data for the 4th selected bar
            myBars4->setWidth(barWidth);
            myBars4->setBrush(QBrush(colourSelect->getColour(barsAdded)));
            myBars4->setName(cityName);
            ui->customPlot->addPlottable(myBars4);
            myBars4->setData(barValueYears,cityData);

            //! Set data for the 4th selected line
            myLines4->setPen(QPen(colourSelect->getColour(barsAdded)));
            myLines4->setName(cityName); //! Names the line "Barrie"
            ui->lineGraph->addPlottable(myLines4);   //!add the line plot to graph
            myLines4->setData(valueYears, cityData);
        }
        else if(j==4)
        {
            //! Set data for the 5th selected bar
            myBars5->setWidth(barWidth);
            myBars5->setBrush(QBrush(colourSelect->getColour(barsAdded)));
            myBars5->setName(cityName);
            ui->customPlot->addPlottable(myBars5);
            myBars5->setData(barValueYears,cityData);

            //! Set data for the 5th selected line
            myLines5->setPen(QPen(colourSelect->getColour(barsAdded)));
            myLines5->setName(cityName); //! Names the line "Barrie"
            ui->lineGraph->addPlottable(myLines5);   //!add the line plot to graph
            myLines5->setData(valueYears, cityData);
        }
        else if(j==5)
        {
            //! Set data for the 6th selected bar
            myBars6->setWidth(barWidth);
            myBars6->setBrush(QBrush(colourSelect->getColour(barsAdded)));
            myBars6->setName(cityName);
            ui->customPlot->addPlottable(myBars6);
            myBars6->setData(barValueYears,cityData);

            //! Set data for the 6th selected line
            myLines6->setPen(QPen(colourSelect->getColour(barsAdded)));
            myLines6->setName(cityName); //! Names the line "Barrie"
            ui->lineGraph->addPlottable(myLines6);   //!add the line plot to graph
            myLines6->setData(valueYears, cityData);
        }
        else if(j==6)
        {
            //! Set data for the 7th selected bar
            myBars7->setWidth(barWidth);
            myBars7->setBrush(QBrush(colourSelect->getColour(barsAdded)));
            myBars7->setName(cityName);
            ui->customPlot->addPlottable(myBars7);
            myBars7->setData(barValueYears,cityData);

            //! Set data for the 7th selected line
            myLines7->setPen(QPen(colourSelect->getColour(barsAdded)));
            myLines7->setName(cityName); //! Names the line "Barrie"
            ui->lineGraph->addPlottable(myLines7);   //!add the line plot to graph
            myLines7->setData(valueYears, cityData);
        }
        else if(j==7)
        {
            //! Set data for the 8th selected bar
            myBars8->setWidth(barWidth);
            myBars8->setBrush(QBrush(colourSelect->getColour(barsAdded)));
            myBars8->setName(cityName);
            ui->customPlot->addPlottable(myBars8);
            myBars8->setData(barValueYears,cityData);

            //! Set data for the 8th selected line
            myLines8->setPen(QPen(colourSelect->getColour(barsAdded)));
            myLines8->setName(cityName); //! Names the line "Barrie"
            ui->lineGraph->addPlottable(myLines8);   //!add the line plot to graph
            myLines8->setData(valueYears, cityData);
        }
        else if(j==8)
        {
            //! Set data for the 9th selected bar
            myBars9->setWidth(barWidth);
            myBars9->setBrush(QBrush(colourSelect->getColour(barsAdded)));
            myBars9->setName(cityName);
            ui->customPlot->addPlottable(myBars9);
            myBars9->setData(barValueYears,cityData);

            //! Set data for the 9th selected line
            myLines9->setPen(QPen(colourSelect->getColour(barsAdded)));
            myLines9->setName(cityName); //! Names the line "Barrie"
            ui->lineGraph->addPlottable(myLines9);   //!add the line plot to graph
            myLines9->setData(valueYears, cityData);
        }
        else if(j==9)
        {
            //! Set data for the 10th selected bar
            myBars10->setWidth(barWidth);
            myBars10->setBrush(QBrush(colourSelect->getColour(barsAdded)));
            myBars10->setName(cityName);
            ui->customPlot->addPlottable(myBars10);
            myBars10->setData(barValueYears,cityData);

            //! Set data for the 10th selected line
            myLines10->setPen(QPen(colourSelect->getColour(barsAdded)));
            myLines10->setName(cityName); //! Names the line "Barrie"
            ui->lineGraph->addPlottable(myLines10);   //!add the line plot to graph
            myLines10->setData(valueYears, cityData);
        }
        else if(j==10)
        {
            //! Set data for the 11th selected bar
            myBars11->setWidth(barWidth);
            myBars11->setBrush(QBrush(colourSelect->getColour(barsAdded)));
            myBars11->setName(cityName);
            ui->customPlot->addPlottable(myBars11);
            myBars11->setData(barValueYears,cityData);

            //! Set data for the 11th selected line
            myLines11->setPen(QPen(colourSelect->getColour(barsAdded)));
            myLines11->setName(cityName); //! Names the line "Barrie"
            ui->lineGraph->addPlottable(myLines11);   //!add the line plot to graph
            myLines11->setData(valueYears, cityData);
        }
        else if(j==11)
        {
            //! Set data for the 12th selected bar
            myBars12->setWidth(barWidth);
            myBars12->setBrush(QBrush(colourSelect->getColour(barsAdded)));
            myBars12->setName(cityName);
            ui->customPlot->addPlottable(myBars12);
            myBars12->setData(barValueYears,cityData);

            //! Set data for the 12th selected line
            myLines12->setPen(QPen(colourSelect->getColour(barsAdded)));
            myLines12->setName(cityName); //! Names the line "Barrie"
            ui->lineGraph->addPlottable(myLines12);   //!add the line plot to graph
            myLines12->setData(valueYears, cityData);
        }


        //! Rescales and replots bar graph
        ui->customPlot->rescaleAxes();
        ui->customPlot->replot();

        //!make graph draggable and plotted items selectable
        ui->customPlot->setInteraction(QCP::iRangeDrag,true);
        ui->customPlot->setInteraction(QCP::iSelectPlottables,true);
        ui->customPlot->xAxis->setRange(2007,2013);

        ui->lineGraph->xAxis->setRange(2007,2013);

        //! Plots City to the line graph
        ui->lineGraph->rescaleAxes();
        ui->lineGraph->replot();

    }
}



/*!
 * \brief MainWindow::slot_refresh_sub Dynamically refreshes the services list
 */
void MainWindow::slot_refresh_sub(){
    ds = new DataSearch();


    ui->list_sub->clear();


    QList<QString> *query_list = new QList<QString>();
    for (int i=0; i<ui->list_services->selectedItems().size(); ++i){
        query_list->append(ui->list_services->selectedItems().at(i)->text());
    }

    returned_list = new QList<QString>();
    returned_listRef = new QList<QString>();
    for (int i = 0; i< query_list->size(); ++i){
        if(query_list->at(i).toStdString().compare("Fire") == 0){
            returned_list->append(ds->getSubDirectory("FIRE%"));
            returned_listRef->append(ds->getSubDirectoryRef("FIRE%"));
        }
        if(query_list->at(i).toStdString().compare("Libraries") == 0){
            returned_list->append(ds->getSubDirectory("PLIB%"));
            returned_listRef->append(ds->getSubDirectoryRef("PLIB%"));
        }
        if(query_list->at(i).toStdString().compare("Parks") == 0){
            returned_list->append(ds->getSubDirectory("PRKS%"));
            returned_listRef->append(ds->getSubDirectoryRef("PRKS%"));
        }
        if(query_list->at(i).toStdString().compare("Waste Management") == 0){
            returned_list->append(ds->getSubDirectory("SWST%"));
            returned_listRef->append(ds->getSubDirectoryRef("SWST%"));
        }
        if(query_list->at(i).toStdString().compare("Police") == 0){
            returned_list->append(ds->getSubDirectory("PLCE%"));
            returned_listRef->append(ds->getSubDirectoryRef("PLCE%"));
        }
        if(query_list->at(i).toStdString().compare("Water") == 0){
            returned_list->append(ds->getSubDirectory("WATR%"));
            returned_listRef->append(ds->getSubDirectoryRef("WATR%"));
        }
    }


    ui->list_sub->addItems(*returned_list);
}

/*!
 * \brief MainWindow::slot_search Preparer function for other ones
 */
void MainWindow::slot_search(){

    std::string *cities_selected = new std::string();
    for (int i=0; i<ui->list_cities->selectedItems().size(); ++i){
        cities_selected->append(ui->list_cities->selectedItems().at(i)->text().toStdString());
        if(i<(ui->list_cities->selectedItems().size()-1))
            cities_selected->append("','");
        else{}
    }

    std::string *years_selected = new std::string();
    for (int i=0; i<ui->list_years->selectedItems().size(); ++i){
        years_selected->append(ui->list_years->selectedItems().at(i)->text().toStdString());
        if(i<(ui->list_years->selectedItems().size()-1))
            years_selected->append("','");
        else{}
    }

    std::string services_selected;

    services_selected = returned_listRef->at(ui->list_sub->SelectRows).toStdString();

    QSqlQuery query = ds->searchForGraphable("MeasureData","*","Year",*years_selected,"Municipality",*cities_selected,"MeasureID",services_selected);
    DataToTable(query);
    query = ds->searchForGraphable("MeasureData","*","Year",*years_selected,"Municipality",*cities_selected,"MeasureID",services_selected);
    DataToGraph(DataToVectors(query));

}

/*!
 * \brief MainWindow::createActions Setting up things
 */
void MainWindow::createActions()
{
    //! Images for each items
    QPixmap quitpix("../src/img/quit.png");
    QPixmap startpix("../src/img/start.png");
    QPixmap aboutpix("../src/img/about.png");

    exit = new QAction(quitpix,"&Quit", this);
    exit->setStatusTip(tr("Quit the program"));
    connect(exit, SIGNAL(triggered()), qApp, SLOT(quit()));


    start = new QAction(startpix,"&Get Started",this);
    start->setStatusTip(tr("Learn how to use this program"));
    connect(start,SIGNAL(triggered()),this,SLOT(get_started_info()));

    about = new QAction(aboutpix,"&About",this);
    about->setStatusTip(tr("About this program"));
    connect(about,SIGNAL(triggered()),this,SLOT(about_info()));

    welcome = new QAction ("&Welcome Screen",this);
    welcome ->setStatusTip(tr("Go back to welcome screen"));
    connect(welcome,SIGNAL(triggered()), this, SLOT(welcome_screen()));

}

/*!
 * \brief MainWindow::createMenus  Create menu with items.
 * This function is responsible for creating the menu items such as help
 */
void MainWindow::createMenus()
{
    home = menuBar()->addMenu(tr("&Home")); //! Adding a home item
    home->addAction(welcome);
    home->addSeparator();
    home->addAction(exit);

    help = menuBar()->addMenu(tr("H&elp"));
    help->addAction(start);
    help->addAction(about);


}
/*!
 *  Display the welcome screen from home menu
 */
void MainWindow::welcome_screen()
{
    ui->stackedWidget->setCurrentIndex(0);
}

/*!
 * \brief MainWindow::get_started_info Display the quick start window
 *  This function is responsible for opening the quick start window
 */
void MainWindow::get_started_info()
{
    quickstart = new get_started(this);
    quickstart->setModal(true); // if you need it.
    quickstart->show();
}

/*!
 * \brief MainWindow::about_info Display the about information
 *  This function is responsible for displaying a message if the user clicks the about item
 */
void MainWindow::about_info()
{

    QMessageBox aboutBox;
    QSpacerItem* horizontalSpacer = new QSpacerItem(400, 300, QSizePolicy::Minimum, QSizePolicy::Expanding);
    aboutBox.setWindowTitle( "About This Software" );
    aboutBox.setIconPixmap(QPixmap("../src/img/info.png"));
    aboutBox.setText( "This program is developed by Group 6\nFor more information please contact the group memebers" );
    QGridLayout* layout = (QGridLayout*)aboutBox.layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    aboutBox.exec();

}
/*!
 * \brief MainWindow::on_continue_button_clicked  Continue to the program
 *  Allowing user to continue to the program after viewing the welcome screen
 */
void MainWindow::on_continue_button_clicked()
{
    ui->button_bar_graph->show();
    ui->button_line_graph->show();
    ui->button_table_view->show();
    ui->button_menu->show();
    current = this->ui->stackedWidget->currentIndex();
    this->ui->stackedWidget->setCurrentIndex(current+1);
}

/*!
 * \brief MainWindow::on_button_bar_graph_clicked Switch between stacked widgets
 *  This function has all the buttons which are responsible for switching th stack widgets
 */
void MainWindow::on_button_bar_graph_clicked()
{
    if (ui->list_cities->selectedItems().count() > 0
            & ui->list_services->selectedItems().count() > 0
            & ui->list_sub->selectedItems().count() > 0
            & ui->list_years->selectedItems().count() > 0 ){
    ui->button_bar_graph->show();
    ui->button_line_graph->show();
    ui->button_table_view->show();
    ui->button_menu->show();
    ui->stackedWidget->setCurrentIndex(3);
    slot_search();
    }
}

/*!
 * \brief MainWindow::on_button_table_view_clicked Deals with table view buttons
 */
void MainWindow::on_button_table_view_clicked()
{
    if (ui->list_cities->selectedItems().count() > 0
            & ui->list_services->selectedItems().count() > 0
            & ui->list_sub->selectedItems().count() > 0
            & ui->list_years->selectedItems().count() > 0 ){
    ui->button_bar_graph->show();
    ui->button_line_graph->show();
    ui->button_table_view->show();
    ui->button_menu->show();
    ui->stackedWidget->setCurrentIndex(2);
    slot_search();
    }
}


/*!
 * \brief MainWindow::on_button_menu_clicked selection view buttons
 */
void MainWindow::on_button_menu_clicked()
{
    ui->button_bar_graph->show();
    ui->button_line_graph->show();
    ui->button_table_view->show();
    ui->button_menu->show();
    ui->stackedWidget->setCurrentIndex(1);
}


/*!
 * \brief MainWindow::on_button_line_graph_clicked line graph view buttons
 */
void MainWindow::on_button_line_graph_clicked()
{
    if (ui->list_cities->selectedItems().count() > 0
            & ui->list_services->selectedItems().count() > 0
            & ui->list_sub->selectedItems().count() > 0
            & ui->list_years->selectedItems().count() > 0 ){
    ui->button_bar_graph->show();
    ui->button_line_graph->show();
    ui->button_table_view->show();
    ui->button_menu->show();
    ui->stackedWidget->setCurrentIndex(4);
    slot_search();
    }
}


/*!
 * \brief MainWindow::on_Button_csv_clicked Export the table data to a csv file
 *  This function export all the data showed in the table view mode
 */
void MainWindow::on_Button_csv_clicked()
{
    QString saveFilename = QFileDialog::getSaveFileName(this, "Save as", "TableView.csv", ".csv");

    QFile f( saveFilename );


    if (f.open(QFile::WriteOnly | QFile::Truncate))
    {
        QTextStream data( &f );
        QStringList strList;

        for( int r = 0; r < ui->tableWidget->rowCount(); ++r )
        {
            strList.clear();
            for( int c = 0; c < ui->tableWidget->columnCount(); ++c )
            {
                //strList << "\" "+ui->tableWidget->horizontalHeaderItem(c)->data(Qt::DisplayRole).toString() +"\" ";
                strList << "\" "+ui->tableWidget->item( r, c )->text()+"\" ";

            }
            data << strList.join( ";" )+"\n";
        }
        f.close();
    }
}

/*!
 * \brief MainWindow::on_Button_clear_all_clicked clear the data selection
 * This function will clear all the data which were selected by user in selection screen
*/
void MainWindow::on_Button_clear_all_clicked()
{
    ui->list_years->clearSelection();
    ui->list_services->clearSelection();
    ui->list_cities->clearSelection();
}



