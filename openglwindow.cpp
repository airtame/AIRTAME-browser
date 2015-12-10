#include <QQmlProperty>
#include "openglwindow.h"



#define QML_URL ""

#define QML_DATA        \
    "\n"                    \
    "import QtQuick 2.0\n"  \
    "import QtWebKit 3.0\n" \
    "\n"                    \
    "WebView {\n"           \
    "    id : webView\n"    \
    "    width:  1080\n"  \
    "    height: 1920\n"  \
    "    \n" \
    "}"

QQuickViewWindow::QQuickViewWindow(QWindow* parent) : QQuickView(parent), m_engine(), m_component(&m_engine),  m_webview(NULL)
{

    //Creation from a local file should be instant. Therefore we keep it simple.
    m_component.setData(QByteArray(QML_DATA), QUrl(QML_URL));
    if (m_component.isError())
    {
        QList<QQmlError> errors = m_component.errors();
        for (int i = 0; i < errors.size(); ++i)
            qDebug() << errors.at(i).toString();
    }
    qDebug()<<"component status:" << m_component.status();
    Q_ASSERT(QQmlComponent::Ready == m_component.status());

    m_webview = m_component.create();
    Q_ASSERT(NULL != m_webview);


    m_view.setResizeMode(QQuickView::SizeViewToRootObject);

    m_view.setContent(QUrl(QML_URL),&m_component, m_webview);


}


void QQuickViewWindow::setUrl(const QUrl &url){
    Q_ASSERT(NULL != m_webview);

           QQmlProperty property(m_webview, "url");
           if(property.isValid())
               property.write(url);

}

void QQuickViewWindow::processCommand(QString command) {

}

void QQuickViewWindow::evalJS(const QString jscmd) {

}



