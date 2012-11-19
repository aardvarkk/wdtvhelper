#include <QtXml>
#include <QErrorMessage>
#include <QSettings>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    organization = "Tau Labs";
    application = "WDTVHelper";

    // Create the UI
    ui->setupUi(this);

    // Load our settings
    QSettings settings(organization, application);
    ui->seriesNumberLineEdit->setText(settings.value(ui->seriesNumberLineEdit->objectName()).toString());

    settings.setValue("size", size());
    settings.setValue("pos", pos());

    // Set up data
    api_key = "AB01ECDE21FAB325";
    root_url = "http://www.thetvdb.com";
    mirrors_url = root_url.toString() + "/" + api_key + "/mirrors.xml";

    // If we're done getting the mirrors
    mirrors_ready = false;

    // We want a signal back saying the mirrors are found
    connect(&mirrors_handler, SIGNAL(mirrorsReady()), this, SLOT(mirrorsReady()));

    // Get the mirrors
    QNetworkReply* r = am.get(QNetworkRequest(mirrors_url));
    connect(r, SIGNAL(readyRead()), &mirrors_handler, SLOT(XMLReady()));
}

MainWindow::~MainWindow()
{
    // Save our settings
    QSettings settings(organization, application);
    settings.setValue(ui->seriesNumberLineEdit->objectName(), ui->seriesNumberLineEdit->text());

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

void MainWindow::seriesReady()
{

}

void MainWindow::on_load_clicked()
{
    int series = ui->seriesNumberLineEdit->text().toInt();
    QString series_str = QString::number(series);
    statusBar()->showMessage("Loading series number " + series_str);

    // We want a signal back saying the mirrors are found
    connect(&series_handler, SIGNAL(seriesReady()), this, SLOT(seriesReady()));

    if (!mirrors_ready || mirrors.count() < 1)
    {
        QErrorMessage err;
        err.showMessage("Mirrors are not yet ready");
        err.exec();
        return;
    }

    // Get the series
    QUrl series_url = mirrors[0].url.toString() + "/api/" + api_key + "/series/" + series_str + "/default/";
    QNetworkReply* r = am.get(QNetworkRequest(series_url));
    connect(r, SIGNAL(readyRead()), &series_handler, SLOT(XMLReady()));
}
