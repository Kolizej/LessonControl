#-------------------------------------------------
#
# Project created by QtCreator 2011-06-22T16:16:19
#
#-------------------------------------------------

QT       += core gui network

TARGET = LessonControl
TEMPLATE = app


SOURCES += main.cpp\
        frmconnect.cpp \
    frmclient.cpp \
    frmserver.cpp \
    clsenums.cpp \
    clsglobal.cpp

HEADERS  += frmconnect.h \
    frmclient.h \
    frmserver.h \
    clsenums.h \
    clsglobal.h \
    ClientInformation.h

FORMS    += frmconnect.ui \
    frmclient.ui \
    frmserver.ui

OTHER_FILES += \
    README.txt
