#include <QWebElement>
#include <QWebFrame>
#include <QDebug>
#include "window.h"
#include "webpage.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    AWebPage *page = new AWebPage(parent);
    webView->setPage(page);
    webView->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    webView->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
}

void Window::setUrl(const QUrl &url)
{

    webView->setUrl(url);
}

void Window::evalJS(const QString jscmd)
{
    webView->page()->mainFrame()->evaluateJavaScript(jscmd);
}
