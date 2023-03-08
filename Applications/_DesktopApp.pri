# mark as imposter
DEFINES += NON_DAISY_DEVICE

QT += widgets svg network

macos:include($$PWD/_Common/mac.pri)

include($$PWD/_Common/CommonApp.pri)
include($$PWD/_Common/JSONTools/JSONTools.pri)
include($$PWD/_Common/Remember/Remember.pri)
include($$PWD/../SchweineSystem/src/_MusicTools/MusicTools.pri)
