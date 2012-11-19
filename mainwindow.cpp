#include <QtXml>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Set up data
    mirrors_ready = false;

    // Create the UI
    ui->setupUi(this);

    // Get the mirrors
    QNetworkReply* mirrors = am.get(QNetworkRequest(QUrl("http://www.thetvdb.com/api/AB01ECDE21FAB325/mirrors.xml")));
    connect(mirrors, SIGNAL(readyRead()), &mirrors_handler, SLOT(XMLReady()));

    // We want a signal back saying the mirrors are found
    connect(&mirrors_handler, SIGNAL(mirrorsReady()), this, SLOT(mirrorsReady()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mirrorsReady()
{
    mirrors_ready = true;

    // Store the mirrors
    mirrors = mirrors_handler.getMirrors();

    // Create a message saying how many mirrors we found
    for (int i = 0; i < mirrors.count(); ++i)
    {
        // What does it support?
        QStringList source_for;
        if (mirrors[i].mirror_type && Mirror::kXMLFiles)
            source_for << "XML Files";
        if (mirrors[i].mirror_type && Mirror::kBannerFiles)
            source_for << "Banner Files";
        if (mirrors[i].mirror_type && Mirror::kZipFiles)
            source_for << "Zip Files";

        QStringList msg;
        msg << "Found mirror at" << mirrors[i].url.toString() << "to provide" << source_for.join(", ");
        statusBar()->showMessage(msg.join(" "));
    }
}

