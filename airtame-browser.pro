QT       += webkitwidgets widgets
LIBS     += -lzmq
FORMS     = window.ui
HEADERS   = window.h \
    webpage.h \
    browser.h \
    zmqserver.h
SOURCES   = main.cpp \
            window.cpp \
    webpage.cpp \
    browser.cpp \
    zmqserver.cpp

