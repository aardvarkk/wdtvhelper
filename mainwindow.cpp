#include <QtXml>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Get the mirrors
    QNetworkReply* mirrors = am.get(QNetworkRequest(QUrl("http://www.thetvdb.com/api/AB01ECDE21FAB325/mirrors.xml")));
    connect(mirrors, SIGNAL(readyRead()), &mirrors_handler, SLOT(XMLReady()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

