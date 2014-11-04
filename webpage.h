#ifndef RRWEBPAGE_H
#define RRWEBPAGE_H

#include <QWebPage>
#include <QDebug>

class AWebPage : public QWebPage
{
    Q_OBJECT
public:
    explicit AWebPage(QObject *parent = 0);

protected:
    void javaScriptConsoleMessage( const QString & message, int lineNumber, const QString & sourceID);
};

#endif // RRWEBPAGE_H
