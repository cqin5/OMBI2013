#ifndef CHARTCOLOUR_H
#define CHARTCOLOUR_H

#include <QVector>
#include <QString>
#include <QColor>

class chartcolour
{
public:
    chartcolour();
    ~chartcolour();
    QColor getColour(int);
private:
    QVector<QColor> colourLib;
};

#endif // CHARTCOLOUR_H
