#ifndef WINDOW_H
#define WINDOW_H

#include <QUrl>
#include <QWidget>
//! [Window class definition]
#include "ui_window.h"

class Window : public QWidget, private Ui::Window
{
    Q_OBJECT

public:
    Window(QWidget *parent = 0);
    void setUrl(const QUrl &url);

};
//! [Window class definition]

#endif
