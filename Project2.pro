#-------------------------------------------------
#
# Project created by QtCreator 2019-04-15T19:50:06
#
#-------------------------------------------------

QT       += core gui network\
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Project2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    start.cpp \
    myscene.cpp \
    myitem.cpp \
    dialog.cpp \
    editorscene.cpp \
    promotion.cpp \
    theme.cpp \
    multi.cpp

HEADERS += \
        mainwindow.h \
    start.h \
    myscene.h \
    myitem.h \
    dialog.h \
    editorscene.h \
    promotion.h \
    theme.h \
    multi.h

FORMS += \
        mainwindow.ui \
    start.ui \
    dialog.ui \
    promotion.ui \
    theme.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
