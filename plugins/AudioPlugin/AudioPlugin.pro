QT += gui widgets

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++11

# Include the-libs build tools
include(/usr/share/the-libs/pri/gentranslations.pri)

LIBS += -lKF5PulseAudioQt
INCLUDEPATH += /usr/include/KF5/KF5PulseAudioQt/PulseAudioQt

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    audiochunk.cpp \
    audioquickwidget.cpp \
    common.cpp \
    eventhandler.cpp \
    micchunk.cpp \
    plugin.cpp \
    quickwidgetsink.cpp \
    quickwidgetsinkinput.cpp

HEADERS += \
    audiochunk.h \
    audioquickwidget.h \
    common.h \
    eventhandler.h \
    micchunk.h \
    plugin.h \
    quickwidgetsink.h \
    quickwidgetsinkinput.h

DISTFILES += \
    Plugin.json \
    defaults.conf

unix {
    translations.files = translations/*.qm
    translations.path = /usr/share/thedesk/AudioPlugin/translations

    defaults.files = defaults.conf
    defaults.path = /etc/theSuite/theDesk/AudioPlugin/

    INSTALLS += translations defaults
}

include(../plugins.pri)

FORMS += \
    audioquickwidget.ui \
    quickwidgetsink.ui \
    quickwidgetsinkinput.ui
