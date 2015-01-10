#include <QWebElement>
#include <QWebFrame>
#include "window.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    webView->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    webView->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    QWebSettings *settings = webView->page()->settings();
    settings->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,true);
    settings->setAttribute(QWebSettings::LocalContentCanAccessFileUrls,true);
}

void Window::setUrl(const QUrl &url)
{
    webView->setUrl(url);
}

void Window::evalJS(const QString jscmd)
{
    webView->page()->mainFrame()->evaluateJavaScript(jscmd);
}
