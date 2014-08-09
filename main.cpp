#include <unistd.h>
#include <QtWidgets>
#include <QLocalSocket>
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
    QCommandLineOption urlOption("u", QCoreApplication::translate("main", "URL to load on start"), QCoreApplication::translate("main", "url"));
    parser.addOption(urlOption);

    QCommandLineOption fullscreenOption("f",QCoreApplication::translate("main", "Set browser to be full screen"));
    parser.addOption(fullscreenOption);

    parser.process(app);
    bool fullscreen = parser.isSet(fullscreenOption);

    /* Setup the window */
    Window window;
    window.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    if (parser.isSet(urlOption)) {
        window.setUrl(QUrl(parser.value(urlOption)));
    } else {
        window.setUrl(QUrl("http://www.airtame.com"));
    }

    if (fullscreen) {
        window.showFullScreen();
    } else {
        window.show();
    }
    return app.exec();
}
