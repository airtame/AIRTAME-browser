#ifndef OPENGLWINDOW_H
#define OPENGLWINDOW_H

#include <QQuickView>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QWebView>
#include <QWidget>
#include "iwindow.h"


class QQuickViewWindow : public QQuickView, public IWindow
{
    Q_OBJECT
public:
    explicit QQuickViewWindow(QWindow *parent = 0);
    void setUrl(const QUrl &url);
    void evalJS(const QString jscmd);
    void processCommand(QString command);

signals:

public slots:

private:
    QQuickView m_view;
    QQmlEngine m_engine;
    QQmlComponent m_component;
    QObject* m_webview;
};

#endif // OPENGLWINDOW_H
