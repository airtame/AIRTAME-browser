#include "webpage.h"
#include <QDebug>
#include <QDate>

AWebPage::AWebPage (QObject *parent) :
    QWebPage(parent) {
}

void AWebPage::javaScriptConsoleMessage( const QString & message, int lineNumber, const QString & sourceID )
{
    qDebug() << message << lineNumber << sourceID;
}
