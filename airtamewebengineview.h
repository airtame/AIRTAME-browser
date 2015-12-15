#ifndef AIRTAMEWEBENGINEVIEW_H
#define AIRTAMEWEBENGINEVIEW_H
#include <QObject>
#include <QWidget>
#include <QWebEngineView>
#include "evaljsstrategy.h"

class AirtameWebEngineView : public QWebEngineView, public EvalJsStrategy
{
    Q_OBJECT
public:
    AirtameWebEngineView(QWidget* parent = 0);
    void evalJS(const QString jscmd) Q_DECL_OVERRIDE;

};
#endif // AIRTAMEWEBENGINEVIEW_H
