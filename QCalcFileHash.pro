######################################################################
# Automatically generated by qmake (3.0) ?? ??? 25 10:09:31 2016
######################################################################

TEMPLATE = app
TARGET = qcalcfilehash
INCLUDEPATH += .
DESTDIR = Bin

QT += widgets

#win32:RC_FILE = QCalcFileHash.rc

CONFIG(debug, release|debug){
    MOC_DIR = .build/debug
    OBJECTS_DIR = .build/debug
    UI_DIR = .build/debug
    RCC_DIR = .build/debug
}
CONFIG(release, release|debug){
    MOC_DIR = .build/release
    OBJECTS_DIR = .build/release
    UI_DIR = .build/release
    RCC_DIR = .build/release
}

gcc {
    win32 {
        INCLUDEPATH  += $(CPLUS_INCLUDE_PATH)
        QMAKE_LIBDIR += $(LIBRARY_PATH)
    }

    LIBS += -lssl -lcrypto
    QMAKE_CXXFLAGS += -std=gnu++11
    QMAKE_CXXFLAGS += -pedantic -pedantic-errors
    QMAKE_CXXFLAGS += -Wall -Wextra -Wformat -Wformat-security -Wno-unused-variable -Wno-unused-parameter
    DEFINES += HAVE_GCC
}

TRANSLATIONS = qcalcfilehash_en.ts \
    qcalcfilehash_ru.ts

# Input
SOURCES += main.cpp \
    mainwindow.cpp \
    ThreadCalcHash.cpp

FORMS += \
    mainwindow.ui

HEADERS += \
    mainwindow.h \
    ThreadCalcHash.h
