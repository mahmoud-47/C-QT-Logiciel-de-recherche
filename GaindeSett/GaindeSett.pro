#-------------------------------------------------
#
# Project created by QtCreator 2023-12-09T01:12:09
#
#-------------------------------------------------

QT       += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
greaterThan(QT_MAJOR_VERSION, 4): CONFIG += c++11
lessThan(QT_MAJOR_VERSION, 5): QMAKE_CXXFLAGS += -std=c++11

TARGET = GaindeSett
TEMPLATE = app




SOURCES += main.cpp\
        mainwindow.cpp \
    affiche.cpp \
    recherche.cpp \
    insere.cpp \
    supprimer.cpp \
    tablehachage.cpp \
    base.cpp \
    qcustomplot.cpp \
    gaindeplot.cpp

HEADERS  += mainwindow.h \
    affiche.h \
    databaseheader.h \
    recherche.h \
    insere.h \
    supprimer.h \
    base.h \
    tablehachage.h \
    qcustomplot.h \
    gaindeplot.h

FORMS    += mainwindow.ui \
    affiche.ui \
    recherche.ui \
    insere.ui \
    supprimer.ui \
    gaindeplot.ui

RESOURCES += \
    imgs.qrc

CONFIG += c++11
