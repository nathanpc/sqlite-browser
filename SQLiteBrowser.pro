#-------------------------------------------------
#
# Project created by QtCreator 2013-10-28T07:47:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SQLiteBrowser
TEMPLATE = app

SOURCES += main.cpp\
		mainwindow.cpp \
	sqlhelper.cpp \
    queryfield.cpp

HEADERS  += mainwindow.h \
	sqlhelper.h \
    queryfield.h

FORMS    += mainwindow.ui

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += sqlite3
