#-------------------------------------------------
#
# Project created by QtCreator 2017-09-03T12:24:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LevelCreator
TEMPLATE = app

LIBS += -lSDL2 -lSDL2_image -lSDL2_ttf -ltinyxml2

SOURCES += main.cpp\
        mainwindow.cpp \
    asteroid.cpp \
    asteroidbig.cpp \
    asteroidmiddle.cpp \
    asteroidsmall.cpp \
    entity.cpp \
    sellingpoint.cpp \
    planet.cpp \
    vector2d.cpp \
    animation.cpp \
    button.cpp \
    camera.cpp \
    level.cpp \
    particle.cpp \
    rocket.cpp \
    spaceship.cpp \
    xmlhelper.cpp \
    timer.cpp \
    texture.cpp

HEADERS  += mainwindow.h \
    asteroid.h \
    asteroidbig.h \
    asteroidmiddle.h \
    asteroidsmall.h \
    entity.h \
    sellingpoint.h \
    planet.h \
    vector2d.h \
    animation.h \
    button.h \
    camera.h \
    level.h \
    particle.h \
    rocket.h \
    xmlhelper.h \
    timer.h \
    texture.h \
    spaceship.h

FORMS    += mainwindow.ui

RESOURCES += \
    resources.qrc
