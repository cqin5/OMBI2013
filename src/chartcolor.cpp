#include "chartcolor.h"
/*!
 * Author: Chuhan Qin, Group 6
 * Description: This is the main window which is responsible for creating the graph,
 * data passed to main window through the stub and are used for plotting
 * Date: November 28, 2013
 */



/*!
 * \brief chartcolour::chartcolour A library of eight different colours.
 */
chartcolour::chartcolour()
{
    //! Set a color for each city based on the order of the cities in the list
    colourLib.append(QColor(51,153,51)); //! Modern Green
    colourLib.append(QColor(229,20,0)); //! Modern Red
    colourLib.append(QColor(27,161,226)); //! Modern Blue
    colourLib.append(QColor(240,150,9)); //! Modern Orange
    colourLib.append(QColor(230,113,184)); //! Modern Pink
    colourLib.append(QColor(160,80,0)); //! Modern Brown
    colourLib.append(QColor(0,171,169)); //! Modern Teal
    colourLib.append(QColor(162,0,255)); //! Modern Purple
}

/*!
 * \brief chartcolour::getColour Returns a fancy colour
 * \param i the index of the bar
 * \return QColor based on the index
 */
QColor chartcolour::getColour(int i){
    int code = i;
    if(i>7)
        code = code % 8;
    return colourLib.at(code);
}
