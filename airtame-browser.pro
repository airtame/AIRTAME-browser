QT       += webkitwidgets network widgets
LIBS     += -lzmq
FORMS     = window.ui
HEADERS   = window.h \
    browser.h \
    zmqserver.h
SOURCES   = main.cpp \
            window.cpp \
    browser.cpp \
    zmqserver.cpp

