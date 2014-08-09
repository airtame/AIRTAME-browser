//! [main program]
#include <unistd.h>
#include <QtWidgets>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;
    window.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    
    window.setUrl(QUrl(argv[1]));
    window.showFullScreen();
    return app.exec();
}
//! [main program]
