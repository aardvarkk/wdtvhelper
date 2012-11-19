#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtXml>
#include <QUrl>

#include "mirrorsxmlhandler.h"
#include "seriesxmlhandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    void mirrorsReady();
    void seriesReady();
    
private slots:
    void on_load_clicked();

private:
    Ui::MainWindow* ui;

    QString organization;
    QString application;
    QString api_key;
    QUrl root_url;
    QUrl mirrors_url;

    // For network communication
    QNetworkAccessManager am;

    // Parsers for different calls
    MirrorsXMLHandler mirrors_handler;
    SeriesXMLHandler series_handler;
    QVector<Mirror> mirrors;
    bool mirrors_ready;
};

#endif // MAINWINDOW_H
