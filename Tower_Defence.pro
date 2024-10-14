QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    circle.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    monster.cpp \
    tower1.cpp \
    towerbase.cpp

HEADERS += \
    circle.h \
    def.h \
    mainwindow.h \
    map.h \
    monster.h \
    tower1.h \
    towerbase.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    res.qrc \
    res.qrc \
    res.qrc

DISTFILES += \
    Tower_Defence.pro.user \
    res_of_qt/background1.png \
    res_of_qt/circle.jpg \
    res_of_qt/crystal.png \
    res_of_qt/monster.jpg
