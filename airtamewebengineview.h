#ifndef AIRTAMEWEBENGINEVIEW_H
#define AIRTAMEWEBENGINEVIEW_H
#include <QObject>
#include <QWebEngineView>
#include "evaljsstrategy.h"

class AirtameWebEngineView : public QWebEngineView, public EvalJsStrategy
{
Q_OBJECT
public:
    AirtameWebEngineView(QWidget* parent = 0);
    void evalJS(const QString jscmd);
protected:
    void showEvent(QShowEvent * event);

};
#endif // AIRTAMEWEBENGINEVIEW_H
