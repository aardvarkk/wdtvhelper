#ifndef EPISODE_H
#define EPISODE_H

#include <QDate>
#include <QLocale>
#include <QString>
#include <QDir>
#include <QStringList>
#include <QImage>

#include "series.h"

class Episode
{
public:
    Episode();

    // Save an episode to a given directory with a given filename
    void saveToWDTVXML(QDir const& dir, QString pattern);

    // Save the metathumb for an episode
    void saveMetaThumb(QUrl mirror, QDir const& dir, QString pattern);

    // Resize to desired aspect ratio
    static const int kAspectW = 680;
    static const int kAspectH = 1000;
    void resizeMetaThumb();

    // Utility functions
    QString seasonString() { return "S" + QString::number(season_number).rightJustified(2, '0'); }
    QString episodeString() { return "E" + QString::number(episode_number).rightJustified(2, '0'); }

    int id;
    int combined_episode;
    int combined_season;
    int dvd_chapter;
    int dvd_disc_id;
    QString dvd_episode; // This can be of the form "4.1" if episodes are combined
    int dvd_season;
    QStringList directors;
    int ep_img_flag;
    QString episode_name;
    int episode_number;
    QDate first_aired;
    QStringList guest_stars;
    QString imdb_id;
    QLocale::Language language;
    QString overview;
    QString production_code;
    double rating;
    int rating_count;
    int season_number;
    QStringList writers;
    int absolute_number;
    QString filename;
    long long last_updated;
    int season_id;
    int series_id;

    // All of our series info
    Series series;

    // Our metathumb
    QImage metathumb;
};

#endif // EPISODE_H
