#include <QtXml>
#include <QErrorMessage>
#include <QFileDialog>
#include <QSettings>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Our app!
    organization = "Tau Labs";
    application = "WDTVHelper";

    // Our setup booleans
    mirrors_ready = false;
    series_ready = false;

    // Create the UI
    ui->setupUi(this);

    // Load our settings
    QSettings settings(organization, application);
    ui->seriesNumberLineEdit->setText(settings.value(ui->seriesNumberLineEdit->objectName()).toString());
    ui->savePathLineEdit->setText(settings.value(ui->savePathLineEdit->objectName()).toString());

    settings.setValue("size", size());
    settings.setValue("pos", pos());

    // Set up data
    api_key = "AB01ECDE21FAB325";
    root_url = "http://www.thetvdb.com";
    mirrors_url = root_url.toString() + "/" + api_key + "/mirrors.xml";

    // We want a signal back saying the mirrors are found
    connect(&mirrors_handler, SIGNAL(mirrorsReady()), this, SLOT(mirrorsReady()));

    // We want a signal back saying the series is ready
    connect(&series_handler, SIGNAL(seriesReady()), this, SLOT(seriesReady()));

    // Get the mirrors
    QNetworkReply* r = am.get(QNetworkRequest(mirrors_url));
    connect(r, SIGNAL(finished()), &mirrors_handler, SLOT(XMLReady()));
}

MainWindow::~MainWindow()
{
    // Save our settings
    QSettings settings(organization, application);
    settings.setValue(ui->seriesNumberLineEdit->objectName(), ui->seriesNumberLineEdit->text());
    settings.setValue(ui->savePathLineEdit->objectName(), ui->savePathLineEdit->text());

    delete ui;
}

void MainWindow::mirrorsReady()
{
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

    mirrors_ready = true;
}

void MainWindow::seriesReady()
{
    series = series_handler.getSeries();
    episodes = series_handler.getEpisodes();

    statusBar()->showMessage(series.series_name + " has " + QString::number(episodes.size()) + " episodes");
//    for (int i = 0; i < episodes.size(); ++i)
//        statusBar()->showMessage("Season " + QString::number(episodes[i].season_number) + " Episode " + QString::number(episodes[i].episode_number) + " - " + episodes[i].episode_name);

    series_ready = true;
}

void MainWindow::on_load_clicked()
{
    if (!mirrors_ready || mirrors.count() < 1)
    {
        QErrorMessage err;
        err.showMessage("Mirrors have not been loaded yet");
        err.exec();
        return;
    }

    // Reset data
    series_handler.clear();

    // Start loading
    int series = ui->seriesNumberLineEdit->text().toInt();
    QString series_str = QString::number(series);
    statusBar()->showMessage("Loading series number " + series_str);

    // Get the series
    QUrl series_url = mirrors.first().url.toString() + "/api/" + api_key + "/series/" + series_str + "/all/";
    QNetworkReply* r = am.get(QNetworkRequest(series_url));
    connect(r, SIGNAL(finished()), &series_handler, SLOT(XMLReady()));
}

void MainWindow::on_browseButton_clicked()
{
    // Show the path browser
    QFileDialog dlg;
    dlg.setParent(this);
    dlg.setOption(QFileDialog::ShowDirsOnly);
    dlg.setFileMode(QFileDialog::Directory);
    if (dlg.exec())
        ui->savePathLineEdit->setText(dlg.selectedFiles().first());
}

void MainWindow::on_saveButton_clicked()
{
    // Only allow saving to occur if the series is ready
    if (!series_ready)
    {
        QErrorMessage err;
        err.showMessage("Series has not been loaded yet");
        err.exec();
        return;
    }

    // Get the save path
    QString save_path = ui->savePathLineEdit->text();

    // Does the save path exist?
    if (save_path.length() <= 0 || !QDir(save_path).exists())
    {
        QErrorMessage err;
        err.showMessage("Save path is empty or does not exist");
        err.exec();
    }

    // Go through each of the episodes and write an XML file for it in the save path!
    for (int i = 0; i < episodes.size(); ++i)
    {
        // Generate a pattern for the file
        QString pattern = series.series_name + " " + episodes[i].seasonString() + episodes[i].episodeString();

        // Saving the XML files
        episodes[i].saveToWDTVXML(QDir(save_path), pattern);

        // Saving the .metathumb image
        episodes[i].saveMetaThumb(mirrors.first().url, QDir(save_path), pattern);

        // Update the status
        ui->statusBar->showMessage("Saved " + pattern + " (" + QString::number(i+1) + " of " + QString::number(episodes.size()) + ")");
    }

    ui->statusBar->showMessage("Done");
}
