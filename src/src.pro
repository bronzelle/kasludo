SOURCES += mainwindow.cpp \
 main.cpp \
 kasludolib.cpp \
 aboutkasludo.cpp
HEADERS += mainwindow.h \
 kasludolib.h \
 aboutkasludo.h
TEMPLATE = app
CONFIG += warn_on \
	  thread \
          qt
TARGET = ../bin/kasludo
RESOURCES = application.qrc
FORMS += ../gui/aboutkasludo.ui \
 main.ui


