#include <unistd.h>
#include <QtWidgets>
#include "window.h"

int main(int argc, char *argv[])
{
    /* Initialize the application */
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName("airtame-browser");
    QCoreApplication::setApplicationVersion("1.0");

    /* Parse the cmdline arguments */
    QCommandLineParser parser;
    parser.setApplicationDescription("AIRTAME Browser");
    parser.addHelpOption();
    parser.addVersionOption();
    QCommandLineOption fullscreenOption("f",QCoreApplication::translate("main", "Set browser to be full screen"));
    parser.addOption(fullscreenOption);

    parser.process(app);
    bool fullscreen = parser.isSet(fullscreenOption);

    /* Setup the window */
    Window window;
    window.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    
    window.setUrl(QUrl(argv[1]));
    if (fullscreen) {
        window.showFullScreen();
    } else {
        window.show();
    }
    return app.exec();
}
