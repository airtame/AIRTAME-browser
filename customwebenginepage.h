#ifndef CUSTOMWEBENGINEPAGE_H
#define CUSTOMWEBENGINEPAGE_H

#include <QWebEnginePage>

class CustomWebenginePage : public QWebEnginePage
{
public:
    CustomWebenginePage();
protected:
    virtual bool certificateError(const QWebEngineCertificateError & certificateError);
    virtual void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString & message, int lineNumber, const QString & sourceID);
};

#endif // CUSTOMWEBENGINEPAGE_H
