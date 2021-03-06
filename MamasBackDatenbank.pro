#-------------------------------------------------
#
# Project created by QtCreator 2018-09-27T18:20:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RezeptManager
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
    recipe.cpp \
    ingredient.cpp \
    recipemanager.cpp \
    iomanager.cpp \
    stardelegate.cpp \
    starrating.cpp \
    stareditor.cpp \
    recipecompare.cpp \
    createpage.cpp \
    searchpage.cpp \
    homepage.cpp \
    recipesearchresultframe.cpp \
    clickablelabel.cpp \
    parameterbutton.cpp \
    pathpixmap.cpp \
    recipeframe.cpp \
    changedialog.cpp

HEADERS += \
        mainwindow.h \
    recipe.h \
    ingredient.h \
    recipemanager.h \
    iomanager.h \
    stardelegate.h \
    starrating.h \
    stareditor.h \
    recipecompare.h \
    createpage.h \
    searchpage.h \
    homepage.h \
    recipesearchresultframe.h \
    clickablelabel.h \
    parameterbutton.h \
    pathpixmap.h \
    recipeframe.h \
    changedialog.h

FORMS += \
        mainwindow.ui \
    changedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    background.qrc

DISTFILES +=

QT += printsupport

win32:RC_ICONS += book_icon.ico
