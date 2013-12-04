/*!
 * Authors: Vietca Vo, Fraser Filice, Chuhan Qin, Stephan De Jegar, Sohrab Dolatabadi, Group 6
 * Description: This is the welcome screen, which displays a debrief of OMBI as well as a
 * tutorial for those new to the program.
 * Date: November 29, 2013
 */

#ifndef GET_STARTED_H
#define GET_STARTED_H

#include <QDialog>
#include "ui_get_started.h"

class get_started : public QDialog
{
    Q_OBJECT
public:
    explicit get_started(QWidget *parent = 0);
    double curr;

private slots:
    void on_next_button_clicked();

    void on_back_button_clicked();

private:
    Ui:: get_started *ui;
};


#endif // GET_STARTED_H
