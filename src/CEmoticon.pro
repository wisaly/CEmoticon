#-------------------------------------------------
#
# Project created by QtCreator 2014-01-24T11:45:54
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CEmoticon
TEMPLATE = app


SOURCES += main.cpp\
    dlg/dlgconfig.cpp \
    xml/xml.cpp \
    xml/xmlnode.cpp \
    xml/xmlnodes.cpp \
    acckey/acckeys.cpp \
    acckey/acckeythread.cpp \
    acckey/acckeynotifier.cpp \
    common/singleapplication.cpp \
    config/appconfig.cpp \
    config/emoconfig.cpp \
    cetabctrl/cetabctrl.cpp \
    cetabctrl/cepaintunit.cpp \
    cetabctrl/cetabitem.cpp \
    cetabctrl/cetabpage.cpp

HEADERS  += common/common.h \
    common/singleapplication.h \
    dlg/dlgconfig.h \
    xml/xml.h \
    xml/xmlnode.h \
    xml/xmlnodes.h \
    acckey/acckeys.h \
    acckey/acckeythread.h \
    acckey/acckeynotifier.h \
    config/appconfig.h \
    config/emoconfig.h \
    cetabctrl/cetabctrl.h \
    cetabctrl/cepaintunit.h \
    cetabctrl/cetabitem.h \
    cetabctrl/cetabpage.h

FORMS    += dlgconfig.ui \
    cetabctrl/cetabctrl.ui

OTHER_FILES += \
    winrc.rc \
    AppConfig.xml

win32: RC_FILE = winrc.rc

win32 {
    debug {
        QMAKE_POST_LINK = $$quote(cmd /c copy /y ..\src\AppConfig.xml debug\\)
    }
    else {
       # TODO: Unices
    }
}


include(qxt/qxtglobalshortcut.pri)
