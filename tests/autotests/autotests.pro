include($$PWD/../../src/defines.pri)

isEqual(QT_MAJOR_VERSION, 5) {
    QT += webkitwidgets network widgets printsupport sql script gui-private testlib
} else {
    QT += core gui webkit sql network script
    CONFIG += qtestlib
}

TARGET = autotests

!unix|mac: LIBS += -L$$PWD/../../bin -lQupZilla
!mac:unix: LIBS += $$PWD/../../bin/libQupZilla.so

QMAKE_LFLAGS+=$${QMAKE_LFLAGS_RPATH}$$PWD/../../bin

# KWallet plugin
isEqual(QT_MAJOR_VERSION, 4):exists($$PWD/../../bin/plugins/libKWalletPasswords.so) {
    LIBS += $$PWD/../../bin/plugins/libKWalletPasswords.so
    DEFINES += HAVE_KDE_PASSWORDS_PLUGIN
}

# GnomeKeyring plugin
exists($$PWD/../../bin/plugins/libGnomeKeyringPasswords.so) {
    LIBS += $$PWD/../../bin/plugins/libGnomeKeyringPasswords.so
    DEFINES += HAVE_GNOME_PASSWORDS_PLUGIN
}


DESTDIR = 
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
UI_DIR = build

INCLUDEPATH += $$PWD/../../src/lib/3rdparty \
               $$PWD/../../src/lib/adblock \
               $$PWD/../../src/lib/app \
               $$PWD/../../src/lib/autofill \
               $$PWD/../../src/lib/bookmarks \
               $$PWD/../../src/lib/cookies \
               $$PWD/../../src/lib/downloads \
               $$PWD/../../src/lib/history \
               $$PWD/../../src/lib/navigation \
               $$PWD/../../src/lib/network \
               $$PWD/../../src/lib/notifications \
               $$PWD/../../src/lib/opensearch \
               $$PWD/../../src/lib/other \
               $$PWD/../../src/lib/plugins \
               $$PWD/../../src/lib/popupwindow \
               $$PWD/../../src/lib/preferences \
               $$PWD/../../src/lib/rss \
               $$PWD/../../src/lib/session \
               $$PWD/../../src/lib/sidebar \
               $$PWD/../../src/lib/tabwidget \
               $$PWD/../../src/lib/tools \
               $$PWD/../../src/lib/webkit \
               $$PWD/../../src/lib/webtab \

HEADERS += \
    qztoolstest.h \
    formcompletertest.h \
    cookiestest.h \
    downloadstest.h \
    adblocktest.h \
    updatertest.h \
    pactest.h \
    passwordbackendtest.h \
    networktest.h

SOURCES += \
    qztoolstest.cpp \
    main.cpp \
    formcompletertest.cpp \
    cookiestest.cpp \
    downloadstest.cpp \
    adblocktest.cpp \
    updatertest.cpp \
    pactest.cpp \
    passwordbackendtest.cpp \
    networktest.cpp
