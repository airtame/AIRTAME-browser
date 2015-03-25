#include <QWebElement>
#include <QWebFrame>
#include <QDebug>
#include <QString>
#include "window.h"
#include "webpage.h"

class VideoPlayer {
    public:
    void resume() {
        qDebug() << "Pausing";
    }
    void pause() {
        qDebug() << "Pausing";
    }
    void playURL(const QString& url) {
        qDebug() << "PLaying back the URL " << url;
    }
};


class VideoPlayerItf : public QObject
{
    Q_OBJECT
private:
    VideoPlayer *mPlayer;
public:
    VideoPlayerItf(QObject *parent = 0) {
    }
    void setVideoPlayer(VideoPlayer *player) {
        mPlayer = player;
    }
public slots:
    void resume() {
        mPlayer->resume();
    }
    void pause() {
        mPlayer->pause();
    }
    void playURL(const QString& url) {
        // this will be called from javascript with: VideoPlayeritf.playURL('youtue.mp4');
        mPlayer->playURL(url);
    }
};

Window::Window(QWidget *parent)
    : QWidget(parent)
{
    setupUi(this);
    AWebPage *page = new AWebPage(parent);
    VideoPlayer *videoPlayer = new VideoPlayer;
    VideoPlayerItf *vPlayerItf = new VideoPlayerItf;

    vPlayerItf->setVideoPlayer(videoPlayer);
    page->mainFrame()->addToJavaScriptWindowObject("NativeVideoPlayer", vPlayerItf);

    webView->setPage(page);
    webView->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    webView->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
}

void Window::setUrl(const QUrl &url)
{

    webView->setUrl(url);
}

void Window::evalJS(const QString jscmd)
{
    webView->page()->mainFrame()->evaluateJavaScript(jscmd);
}
