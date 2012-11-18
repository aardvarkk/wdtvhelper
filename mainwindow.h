#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
#include <QtXml>

#include "mirrorsxmlhandler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow* ui;

    // For network communication
    QNetworkAccessManager am;

    // Parsers for different calls
    MirrorsXMLHandler mirrors_handler;
};

#endif // MAINWINDOW_H
