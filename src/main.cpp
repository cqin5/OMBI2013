/*!
 * Authors: Vietca Vo, Fraser Filice, Chuhan Qin, Stephan De Jegar, Sohrab Dolatabadi, Group 6
 * Description: This is the main class, which is responsible for launching the program.
 * Date: November 29, 2013
 */

#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>

/*!
 * \brief main  Main function responsbile for launching the program.
 * \param argc
 * \param argv
 * \return
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QFont font;
    font.setFamily("Serif");
    app.setFont(font);

    //! The resource directories for the loading screen
    QPixmap splash_0("../src/img/splash_0.png");
    QPixmap splash_1("../src/img/splash_1.png");
    QPixmap splash_2("../src/img/splash_2.png");
    QPixmap splash_3("../src/img/splash_3.png");

    //! Creates the loading screen
    QSplashScreen splash_screen_0(splash_0);
    splash_screen_0.setAttribute(Qt::WA_TranslucentBackground);
    QSplashScreen splash_screen_1(splash_1);
    QSplashScreen splash_screen_2(splash_2);
    QSplashScreen splash_screen_3(splash_3);

    MainWindow w;
    w.setWindowTitle("OMBI 2013");  //! Sets and displays program name

    //! Runs the loading screen effect
    splash_screen_0.show();
    splash_screen_0.finish(&w);

    splash_screen_1.show();
    splash_screen_1.finish(&w);

    splash_screen_2.show();
    splash_screen_2.finish(&w);

    splash_screen_3.show();
    splash_screen_3.finish(&w);

    w.show();
    return app.exec();
}

