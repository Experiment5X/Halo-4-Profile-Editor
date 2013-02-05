TARGET = Halo4Profile

CONFIG(debug, debug|release) {
    #TEMPLATE = app
    CONFIG += plugin debug

    #uncomment the below to build the plugin for debug mode
    TEMPLATE = lib

    HEADERS += \
        DebuggingClass.h

    SOURCES += \
        main.cpp \
        DebuggingClass.cpp
}
CONFIG(release, debug|release) {
    TEMPLATE = lib
    CONFIG += plugin release
}

# flags
QMAKE_CXXFLAGS += -fpermissive

INCLUDEPATH += $$PWD/include

win32:LIBS += -L$$PWD/include/ -lXboxInternals
win32:INCLUDEPATH += "C:/botan/include"
win32:LIBS += -LC:/botan/ -lBotan

unix:INCLUDEPATH += "/usr/local/include/botan-1.10"
unix:LIBS += "/usr/local/lib/libbotan-1.10.a"

VERSION = 1.0.0
INSTALLS += target

HEADERS += \
    Halo4ProfileDialog.h \
    igpdmodder.h \
    BitArray.h

SOURCES += \
    Halo4ProfileDialog.cpp \
    BitArray.cpp

FORMS += \
    Halo4ProfileDialog.ui

RESOURCES += \
    resources.qrc
