#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QImage>
#include <QObject>
#include <QtNetwork>

class Downloader : public QObject
{
    Q_OBJECT

public:
    Downloader();

    // When a call completes
    void contentReceived(QNetworkReply* reply);

    // download an image from a url (blocking!)
    void downloadImage(QUrl url, QImage& img);

private:
    // Required for net calls
    QNetworkAccessManager am;

    // Downloaded content
    QByteArray content;
};

#endif // DOWNLOADER_H
