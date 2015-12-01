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
    //set the webpage settings globally
    QWebSettings *settings = QWebSettings::globalSettings();
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

void Window::processCommand(QString cmd)
{

    QStringList pieces = cmd.split("\n");

    // Process the commands coming through the socket!
    foreach(QString line, pieces) {
        QStringList vals = line.split(" ");
        if (vals.at(0) == "URL" && vals.length() > 1) {
            qDebug() << "Changing URL to: " << vals.at(1);
            setUrl(vals.at(1));
        }
        if (vals.at(0) == "EVAL" && vals.length() > 1) {
            vals.removeAt(0);
            QString fullcmd = vals.join(" ");
            qDebug() << "Evaling JS: " << fullcmd;
            evalJS(fullcmd);
        }
        if (vals.at(0) == "SHOW") {
            qDebug() << "Show browser";
            show();
        }
        if (vals.at(0) == "HIDE") {
            qDebug() << "Hide browser";
            hide();
        }
    }
}
