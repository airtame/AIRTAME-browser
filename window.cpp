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
        // FIXME: join stutfz
        if (vals.at(0) == "EVAL" && vals.length() > 1) {
            qDebug() << "Evaling JS: " << vals.at(1);
            evalJS(vals.at(1));
        }
    }

}
