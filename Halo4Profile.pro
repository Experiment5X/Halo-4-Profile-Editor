TARGET = Halo4Profile

DEFINES += SHOW_UI

CONFIG(debug, debug|release) {
    TEMPLATE = app
    CONFIG += plugin debug

    #uncomment the below to build the plugin for debug mode
    #TEMPLATE = lib

    HEADERS += \
        DebuggingClass.h \
        Stfs/StfsPackage.h \
        Stfs/StfsMetaData.h \
        Stfs/StfsDefinitions.h \
        Stfs/StfsConstants.h

    SOURCES += \
        main.cpp \
        DebuggingClass.cpp \
        Stfs/StfsPackage.cpp \
        Stfs/StfsMetaData.cpp \
        Stfs/StfsDefinitions.cpp
}
CONFIG(release, debug|release) {
    TEMPLATE = lib
    CONFIG += plugin release
}

win32:include(Stfs/Botan.pri)
win32:INCLUDEPATH += "C:/botan/include"
win32:LIBS += "C:/botan/libBotan.a"

unix:INCLUDEPATH += "/usr/local/include/botan-1.10"
unix:LIBS += "/usr/local/lib/libbotan-1.10.a"

VERSION = 1.0.0
INSTALLS += target

HEADERS += \
    Halo4ProfileDialog.h \
    GPD/XDBFHelpers.h \
    GPD/XDBFDefininitions.h \
    GPD/XDBF.h \
    GPD/GPDBase.h \
    GPD/GameGPD.h \
    igpdmodder.h \
    FileIO.h \
    AvatarAsset/AvatarAssetDefinintions.h \
    AvatarAsset/AvatarAsset.h \
    AvatarAsset/AssetHelpers.h \
    BitArray.h \
    MemoryStream.h

SOURCES += \
    Halo4ProfileDialog.cpp \
    GPD/XDBFHelpers.cpp \
    GPD/XDBF.cpp \
    GPD/GPDBase.cpp \
    GPD/GameGPD.cpp \
    FileIO.cpp \
    AvatarAsset/AvatarAsset.cpp \
    AvatarAsset/AssetHelpers.cpp \
    BitArray.cpp \
    MemoryStream.cpp

FORMS += \
    Halo4ProfileDialog.ui

OTHER_FILES += \
    Stfs/Botan.pri

RESOURCES += \
    resources.qrc
