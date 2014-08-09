#include <QWebElement>
#include <QWebFrame>
#include "window.h"

//! [Window class constructor]
Window::Window(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    webView->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    webView->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
}
//! [Window class constructor]

//! [set URL]
void Window::setUrl(const QUrl &url)
{
    webView->setUrl(url);
}
//! [set URL]
