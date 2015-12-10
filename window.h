#ifndef WINDOW_H
#define WINDOW_H

#include <QUrl>
#include <QtWebEngineWidgets>
#include <QWidget>
//! [Window class definition]
#include "ui_window.h"

class Window : public QWidget, private Ui::Window
{
    Q_OBJECT
private:
    #ifdef QTWEBENGINECORE_VERSION
      QWebEngineView *webView;
    #endif

public:
    Window(QWidget *parent = 0);
    void setUrl(const QUrl &url);
    void evalJS(const QString jscmd);
    void processCommand(QString command);
    void showFullScreen();
    void show();
    void hide();
};
//! [Window class definition]

#endif
