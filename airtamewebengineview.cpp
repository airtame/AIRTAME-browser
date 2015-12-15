#include <QDebug>
#include <QtCore/QTimer>
#include <QWebEngineSettings>
#include "airtamewebengineview.h"
#include "customwebenginepage.h"

AirtameWebEngineView::AirtameWebEngineView(QWidget* parent) : QWebEngineView(parent)
{

    //set the webpage settings globally
    QWebEngineSettings *settings = QWebEngineSettings::globalSettings();
    settings->setAttribute(QWebEngineSettings::LocalContentCanAccessRemoteUrls,true);
    settings->setAttribute(QWebEngineSettings::LocalContentCanAccessFileUrls,true);

    CustomWebenginePage* page = new CustomWebenginePage();
    this->setPage(page);

    //log when the webengine render process finishes
    connect(this, &QWebEngineView::renderProcessTerminated,
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

        qDebug() << "Render process exited with code : " << statusCode << status;
        //reload the page
        QTimer::singleShot(0, [this]{reload(); });
    });
}


void AirtameWebEngineView::evalJS(const QString jscmd)
{
    this->page()->runJavaScript(jscmd, [](const QVariant &result){ qDebug() << result;});
}


