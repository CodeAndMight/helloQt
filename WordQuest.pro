#-------------------------------------------------
#
# Project created by QtCreator 2014-06-30T15:32:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = WordQuest
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    wordquest.cpp

HEADERS  += mainwindow.h \
    wordquest.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resources.qrc

OTHER_FILES += \
    README.md \
    TestTable.txt
