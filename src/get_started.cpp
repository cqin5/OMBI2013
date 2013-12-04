/*!
 * Authors: Vietca Vo, Fraser Filice, Chuhan Qin, Stephan De Jegar, Sohrab Dolatabadi, Group 6
 * Description: This is the welcome screen, which displays a debrief of OMBI as well as a
 * tutorial for those new to the program.
 * Date: November 29, 2013
 */

#include "get_started.h"
#include "ui_get_started.h"
#include <QStyle>

/*!
 * \brief get_started::get_started Loads up the UI of the welcome screen.
 * \param parent
 */
get_started::get_started(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::get_started)
{
    ui->setupUi(this);
    this->setWindowTitle("Qucik Start");
    //! Change the background of the main window
    this->setStyleSheet("QPushButton { background-color: #febf2b;color:#373536;border:1px solid #dcdcdc;padding:5px;width:100px; }");
}

/*!
 * \brief get_started::on_next_button_clicked  Accesses the four step tutorial when the user clicks "next" while
 * on the first stack view.
 */
void get_started::on_next_button_clicked()
{
    curr = this->ui->stackedWidget->currentIndex();
    this->ui->stackedWidget->setCurrentIndex(curr+1);
}

/*!
 * \brief get_started::on_back_button_clicked   Brings the user back to the first stack widget when the user clicks
 * "back" while on the second stack view.
 */
void get_started::on_back_button_clicked()
{
    curr = this->ui->stackedWidget->currentIndex();
    this->ui->stackedWidget->setCurrentIndex(curr-1);
}
