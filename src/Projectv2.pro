#-------------------------------------------------
#
# Project created by QtCreator 2013-10-23T10:08:18
#
#-------------------------------------------------

QT       += core gui sql
addFiles.sources = db.sqlite
addFiles.path = .
DEPLOYMENT += addFiles

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Projectv2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    chartcolor.cpp \
    datasearch.cpp \
    databasehandler.cpp \
    get_started.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    chartcolor.h \
    datasearch.h \
    databasehandler.h \
    get_started.h

FORMS    += mainwindow.ui \
    get_started.ui

RESOURCES += \
    src.qrc
