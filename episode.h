#ifndef EPISODE_H
#define EPISODE_H

#include <QDate>
#include <QLocale>
#include <QString>
#include <QStringList>

class Episode
{
public:
    Episode();

    int id;
    int combined_episode;
    int combined_season;
    int dvd_chapter;
    int dvd_disc_id;
    int dvd_episode;
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
};

#endif // EPISODE_H
