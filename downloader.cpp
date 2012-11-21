#include <QImageReader>

#include "downloader.h"

Downloader::Downloader()
{
}

void Downloader::contentReceived(QNetworkReply* reply)
{
    content = reply->readAll();
}

void Downloader::downloadImage(QUrl url, QImage& img)
{
    // A blocking call
    QEventLoop block;
    QNetworkReply* r = am.get(QNetworkRequest(url));
    connect(r, SIGNAL(finished()), &block, SLOT(quit()));
    block.exec();

    // We have our content, so give it back
    if (r->error() != QNetworkReply::NoError)
    {
        qDebug() << "Error downloading image " << url.toString();
    }

    QImageReader reader(r);
    img = reader.read();

    delete r;
}

