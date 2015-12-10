QT       += webkitwidgets widgets webenginewidgets
LIBS     += -lzmq
FORMS     = window.ui
HEADERS   = window.h \
    browser.h \
    zmqserver.h \
    webpage.h \
    zmq.hpp \
    customwebenginepage.h
SOURCES   = main.cpp \
            window.cpp \
    browser.cpp \
    zmqserver.cpp \
    webpage.cpp \
    customwebenginepage.cpp

