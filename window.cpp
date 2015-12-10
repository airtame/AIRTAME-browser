#include <QWebElement>
#include <QWebFrame>
#include <QtCore/QTimer>
#include <QDebug>
#include "window.h"
#include "webpage.h"
#include "customwebenginepage.h"

Window::Window(QWidget *parent)
    : QWidget(parent)
{
#ifdef QTWEBENGINECORE_VERSION
#pragma message "webengineview"
    webView = new QWebEngineView();
    CustomWebenginePage* page = new CustomWebenginePage();
    webView->setPage(page);

    connect(webView, &QWebEngineView::renderProcessTerminated,
            [=](QWebEnginePage::RenderProcessTerminationStatus termStatus, int statusCode) {
        const char *status = "";
        switch (termStatus) {
        case QWebEnginePage::NormalTerminationStatus:
            status = "(normal exit)";
            break;
        case QWebEnginePage::AbnormalTerminationStatus:
            status = "(abnormal exit)";
            break;
        case QWebEnginePage::CrashedTerminationStatus:
            status = "(crashed)";
            break;
        case QWebEnginePage::KilledTerminationStatus:
            status = "(killed)";
            break;
        }

        qDebug() << "Render process exited with code" << statusCode << status;
        QTimer::singleShot(0, [this] {webView->reload(); });
    });



    //set the webpage settings globally
    QWebEngineSettings *settings = QWebEngineSettings::globalSettings();
    settings->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls,true);
    settings->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls,true);
    QMetaObject::connectSlotsByName(this);
#else
#pragma message "webkit1"
    setupUi(this);
    AWebPage *page = new AWebPage(parent);
    webView->setPage(page);
    webView->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    webView->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    //set the webpage settings globally
    QWebSettings *settings = QWebSettings::globalSettings();
    settings->setAttribute(QWebSettings::LocalContentCanAccessRemoteUrls,true);
    settings->setAttribute(QWebSettings::LocalContentCanAccessFileUrls,true);
#endif


}

void Window::setUrl(const QUrl &url)
{

    webView->setUrl(url);
}

void Window::evalJS(const QString jscmd)
{

#ifdef QTWEBENGINECORE_VERSION
    webView->page()->runJavaScript(jscmd, [](const QVariant &result){ qDebug() << result;});
#else
    webView->page()->mainFrame()->evaluateJavaScript(jscmd);
#endif
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
void Window::showFullScreen() {
#ifdef QTWEBENGINECORE_VERSION
    qDebug() << "webiew fullscreen";
    webView->showFullScreen();
#else
    Window::QWidget.showFullScreen();
#endif
}

void Window::show() {
#ifdef QTWEBENGINECORE_VERSION
    qDebug() << "webiew show";
    webView->show();
#else
    Window::QWidget.show();
#endif
}

void Window::hide() {
#ifdef QTWEBENGINECORE_VERSION
    qDebug() << "webiew hide";
    webView->hide();
#else
    Window::QWidget.hide();
#endif

}
