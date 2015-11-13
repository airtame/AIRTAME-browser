QT       += webkitwidgets widgets
LIBS     += -lzmq
FORMS     = window.ui
HEADERS   = window.h \
<<<<<<< HEAD   (83a062 B/browser: Fixed merge code removal)
            browser.h \
            webpage.h

=======
    browser.h \
    zmqserver.h
>>>>>>> BRANCH (c5bbf5 F/browser: Added support for zmq library + refactoring)
SOURCES   = main.cpp \
            window.cpp \
<<<<<<< HEAD   (83a062 B/browser: Fixed merge code removal)
            webpage.cpp \
            browser.cpp
=======
    browser.cpp \
    zmqserver.cpp
>>>>>>> BRANCH (c5bbf5 F/browser: Added support for zmq library + refactoring)

