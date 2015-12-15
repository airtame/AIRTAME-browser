#include <QDebug>
#include "customwebenginepage.h"

CustomWebenginePage::CustomWebenginePage()
{

}

bool CustomWebenginePage::certificateError(const QWebEngineCertificateError &certificateError) {

    //log and return true to ignore the error for now
    qDebug() << certificateError.errorDescription() << " error code: " << certificateError.error();
    return true;
}

void CustomWebenginePage::javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID){

    qDebug() <<level << message << lineNumber << sourceID;

}

