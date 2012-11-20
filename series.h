#ifndef SERIES_H
#define SERIES_H

#include <QLocale>
#include <QStringList>
#include <QTime>
#include <QUrl>

#include "contentrating.h"
#include "seriesstatus.h"

class Series
{
public:
    Series();

    int id;
    QStringList actors;
    Qt::DayOfWeek airs_dayofweek;
    QTime airs_time;
    ContentRating content_rating;
    QDate first_aired;
    QStringList genres;
    QString imdb_id;
    QLocale::Language language;
    QString network;
    int network_id;
    QString overview;
    double rating;
    int rating_count;
    double runtime;
    int series_id;
    QString series_name;
    SeriesStatus status;
    QDateTime added;
    int added_by;
    QString banner;
    QString fan_art;
    long long last_updated;
    QString poster;
    QString zap2it_id;
};

#endif // SERIES_H
