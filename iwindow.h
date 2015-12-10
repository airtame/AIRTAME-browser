#ifndef IWINDOW
#define IWINDOW

class IWindow  {
public:
    virtual void setUrl(const QUrl &url) = 0;
    virtual void evalJS(const QString jscmd) = 0;
    virtual void processCommand(QString command) = 0;
};

#endif // IWINDOW

