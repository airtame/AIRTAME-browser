#ifndef CUSTOMWEBENGINEPAGE_H
#define CUSTOMWEBENGINEPAGE_H

#include <QWebEnginePage>

class CustomWebenginePage : public QWebEnginePage
{
public:
    CustomWebenginePage();
protected:
    bool certificateError(const QWebEngineCertificateError & certificateError) Q_DECL_OVERRIDE;
    void javaScriptConsoleMessage(JavaScriptConsoleMessageLevel level, const QString & message, int lineNumber, const QString & sourceID) Q_DECL_OVERRIDE;
};

#endif // CUSTOMWEBENGINEPAGE_H
