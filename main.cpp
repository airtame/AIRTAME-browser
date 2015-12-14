#include <unistd.h>
#include <QtWidgets>
#include <QLocalSocket>
#include "browser.h"
#include "window.h"
#include "airtamewebengineview.h"

int main(int argc, char *argv[])
{
    /* Initialize the application */
    try {

        BrowserApplication app(argc, argv);

        QCoreApplication::setApplicationName("airtame-browser");
        QCoreApplication::setApplicationVersion("1.1");

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

        #ifdef QWEBENGINEVIEW_H
         #pragma message "webengine view"
        AirtameWebEngineView window;
        #else
        /* Setup the window */
        Window window;
        #endif

        window.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
        if (parser.isSet(urlOption)) {
            window.setUrl(QUrl(parser.value(urlOption)));
        } else {
            window.setUrl(QUrl("http://localhost/splash/redir.php"));
        }

        if (fullscreen) {
            window.showFullScreen();
        } else {
            window.show();
        }

        /* Give the window ref to the app */
        app.mainWindow = &window;

        /* Execute the app */
        return app.exec();

    } catch (const std::bad_alloc & exception) {
        qDebug() <<__FILE__<< __LINE__<< " bad_alloc caught: " << exception.what();
        return -1; //exit the application in case of memory allocation failure
    }

}
