#-------------------------------------------------
#
# Project created by QtCreator 2018-01-19T11:39:32
#
#-------------------------------------------------

QT       += core gui network

TARGET = chat_item
TEMPLATE = app


SOURCES += main.cpp\
        logindialog.cpp \
    regdialog.cpp \
    friendlistdialog.cpp \
    chatdialog.cpp \
    groupchatdialog.cpp

HEADERS  += logindialog.h \
    regdialog.h \
    friendlistdialog.h \
    chatdialog.h \
    groupchatdialog.h

FORMS    += logindialog.ui \
    regdialog.ui \
    friendlistdialog.ui \
    chatdialog.ui \
    groupchatdialog.ui

RESOURCES += \
    ico.qrc


RC_FILE+= myico.rc
