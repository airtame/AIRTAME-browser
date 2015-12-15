#ifndef WINDOW_H
#define WINDOW_H

#include <QUrl>
#include <QWidget>
//! [Window class definition]
#include "ui_window.h"
#include "evaljsstrategy.h"

class Window : public QWidget, private Ui::Window, public EvalJsStrategy {
    Q_OBJECT
public:
    Window(QWidget *parent = 0);
    void setUrl(const QUrl &url);
    void evalJS(const QString jscmd) Q_DECL_OVERRIDE;

};
//! [Window class definition]

#endif
