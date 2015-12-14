#include <QDebug>
#include "customwebenginepage.h"

CustomWebenginePage::CustomWebenginePage()
{

}

bool CustomWebenginePage::certificateError(const QWebEngineCertificateError &certificateError) {

    qDebug() << certificateError.errorDescription() << " error code: " << certificateError.error();
    //return true to ignore the error
    return true;
}

void CustomWebenginePage::javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID){

qDebug() <<level << message << lineNumber << sourceID;

}

