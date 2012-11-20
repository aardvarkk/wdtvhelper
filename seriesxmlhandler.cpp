#include <QDebug>
#include <QStringRef>

#include "seriesxmlhandler.h"

bool SeriesXMLHandler::startElement(QString const& namespaceURI,  QString const& localName, QString const& qName, QXmlAttributes const& atts)
{
    prev_element = qName;
    return true;
}

bool SeriesXMLHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    if (!qName.compare("Series"))
    {
        series = current_series;
        handling_series = false;
    }
    else if (!qName.compare("Episode"))
    {
        episodes.push_back(current_episode);
    }

    prev_element.clear();

    return true;
}

void SeriesXMLHandler::HandleSeries(QString const& ch)
{
    if (!prev_element.compare("id"))
    {
        current_series.id = ch.toInt();
    }
    else if (!prev_element.compare("Actors"))
    {
        if (ch.length() > 1)
            current_series.actors = ch.mid(1, ch.length()-2).split("|");
    }
    else if (!prev_element.compare("Airs_DayOfWeek"))
    {
        if (!ch.compare("Monday"))
            current_series.airs_dayofweek = Qt::Monday;
        else if (!ch.compare("Tuesday"))
            current_series.airs_dayofweek = Qt::Tuesday;
        else if (!ch.compare("Wednesday"))
            current_series.airs_dayofweek = Qt::Wednesday;
        else if (!ch.compare("Thursday"))
            current_series.airs_dayofweek = Qt::Thursday;
        else if (!ch.compare("Friday"))
            current_series.airs_dayofweek = Qt::Friday;
        else if (!ch.compare("Saturday"))
            current_series.airs_dayofweek = Qt::Saturday;
        else if (!ch.compare("Sunday"))
            current_series.airs_dayofweek = Qt::Sunday;
    }
    else if (!prev_element.compare("Airs_Time"))
    {
        current_series.airs_time = QTime(ch.left(2).toInt(), ch.right(2).toInt());
    }
    else if (!prev_element.compare("ContentRating"))
    {
        if (!ch.compare("TV-Y"))
            current_series.content_rating = TV_Y;
        else if (!ch.compare("TV-Y7"))
            current_series.content_rating = TV_Y7;
        else if (!ch.compare("TV-Y7-FV"))
            current_series.content_rating = TV_Y7_FV;
        else if (!ch.compare("TV-G"))
            current_series.content_rating = TV_G;
        else if (!ch.compare("TV-PG"))
            current_series.content_rating = TV_PG;
        else if (!ch.compare("TV-14"))
            current_series.content_rating = TV_14;
        else if (!ch.compare("TV-MA"))
            current_series.content_rating = TV_MA;
    }
    else if (!prev_element.compare("FirstAired"))
    {
        current_series.first_aired = QDate::fromString(ch, "yyyy-MM-dd");
    }
    else if (!prev_element.compare("Genre"))
    {
        if (ch.length() > 1)
            current_series.genres = ch.mid(1, ch.length()-2).split("|");
    }
    else if (!prev_element.compare("IMDB_ID"))
    {
        current_series.imdb_id = ch;
    }
    else if (!prev_element.compare("Language"))
    {
        for (int i = 0; i <= QLocale::LastLanguage; ++i)
        {
            if (!ch.compare(QLocale::languageToString(static_cast<QLocale::Language>(i))))
                current_series.language = static_cast<QLocale::Language>(i);
        }
    }
    else if (!prev_element.compare("Network"))
    {
        current_series.network = ch;
    }
    else if (!prev_element.compare("NetworkID"))
    {
        current_series.network_id = ch.toInt();
    }
    else if (!prev_element.compare("Overview"))
    {
        current_series.overview = ch;
    }
    else if (!prev_element.compare("Rating"))
    {
        current_series.rating = ch.toDouble();
    }
    else if (!prev_element.compare("RatingCount"))
    {
        current_series.rating_count = ch.toInt();
    }
    else if (!prev_element.compare("Runtime"))
    {
        current_series.runtime = ch.toDouble();
    }
    else if (!prev_element.compare("SeriesID"))
    {
        current_series.series_id = ch.toInt();
    }
    else if (!prev_element.compare("SeriesName"))
    {
        current_series.series_name = ch;
    }
    else if (!prev_element.compare("Status"))
    {
        if (!ch.compare("Continuing"))
            current_series.status = Continuing;
        else if (!ch.compare("Ended"))
            current_series.status = Ended;
        else if (!ch.compare("On Hiatus"))
            current_series.status = On_Hiatus;
        else if (!ch.compare("Other"))
            current_series.status = Other;
    }
    else if (!prev_element.compare("added"))
    {
        current_series.added = QDateTime::fromString(ch, "yyyy-MM-dd HH:mm:ss");
    }
    else if (!prev_element.compare("addedBy"))
    {
        current_series.added_by = ch.toInt();
    }
    else if (!prev_element.compare("banner"))
    {
        current_series.banner = ch;
    }
    else if (!prev_element.compare("fanart"))
    {
        current_series.fan_art = ch;
    }
    else if (!prev_element.compare("lastupdated"))
    {
        current_series.last_updated = ch.toLongLong();
    }
    else if (!prev_element.compare("poster"))
    {
        current_series.poster = ch;
    }
    else if (!prev_element.compare("zap2it_id"))
    {
        current_series.zap2it_id = ch;
    }
}

void SeriesXMLHandler::HandleEpisode(QString const& ch)
{
    if (!prev_element.compare("id"))
    {
        current_episode.id = ch.toInt();
    }
    else if (!prev_element.compare("Combined_episodenumber"))
    {
        current_episode.combined_episode = ch.toInt();
    }
    else if (!prev_element.compare("Combined_season"))
    {
        current_episode.combined_season = ch.toInt();
    }
    else if (!prev_element.compare("DVD_chapter"))
    {
        current_episode.dvd_chapter = ch.toInt();
    }
    else if (!prev_element.compare("DVD_discid"))
    {
        current_episode.dvd_disc_id = ch.toInt();
    }
    else if (!prev_element.compare("DVD_episodenumber"))
    {
        current_episode.dvd_episode = ch.toInt();
    }
    else if (!prev_element.compare("DVD_season"))
    {
        current_episode.dvd_season = ch.toInt();
    }
    else if (!prev_element.compare("Director"))
    {
        if (ch.length() > 1)
            current_episode.directors = ch.mid(1, ch.length()-2).split("|");
    }
    else if (!prev_element.compare("EpImgFlag"))
    {
        current_episode.ep_img_flag = ch.toInt();
    }
    else if (!prev_element.compare("EpisodeName"))
    {
        current_episode.episode_name = ch;
    }
    else if (!prev_element.compare("EpisodeNumber"))
    {
        current_episode.episode_number = ch.toInt();
    }
    else if (!prev_element.compare("FirstAired"))
    {
        current_episode.first_aired = QDate::fromString(ch, "yyyy-MM-dd");
    }
    else if (!prev_element.compare("GuestStars"))
    {
        if (ch.length() > 1)
            current_episode.guest_stars = ch.mid(1, ch.length()-2).split("|");
    }
    else if (!prev_element.compare("IMDB_ID"))
    {
        current_episode.imdb_id = ch;
    }
    else if (!prev_element.compare("Language"))
    {
        for (int i = 0; i <= QLocale::LastLanguage; ++i)
        {
            if (!ch.compare(QLocale::languageToString(static_cast<QLocale::Language>(i))))
                current_episode.language = static_cast<QLocale::Language>(i);
        }
    }
    else if (!prev_element.compare("Overview"))
    {
        current_episode.overview = ch;
    }
    else if (!prev_element.compare("ProductionCode"))
    {
        current_episode.production_code = ch;
    }
    else if (!prev_element.compare("Rating"))
    {
        current_episode.rating = ch.toDouble();
    }
    else if (!prev_element.compare("RatingCount"))
    {
        current_episode.rating_count = ch.toInt();
    }
    else if (!prev_element.compare("SeasonNumber"))
    {
        current_episode.season_number = ch.toInt();
    }
    else if (!prev_element.compare("Writer"))
    {
        if (ch.length() > 1)
            current_episode.writers = ch.mid(1, ch.length()-2).split("|");
    }
    else if (!prev_element.compare("absolute_number"))
    {
        current_episode.absolute_number = ch.toInt();
    }
    else if (!prev_element.compare("filename"))
    {
        current_episode.filename = ch;
    }
    else if (!prev_element.compare("lastupdated"))
    {
        current_episode.last_updated = ch.toLongLong();
    }
    else if (!prev_element.compare("seasonid"))
    {
        current_episode.season_id = ch.toInt();
    }
    else if (!prev_element.compare("seriesid"))
    {
        current_episode.series_id = ch.toInt();
    }
}

bool SeriesXMLHandler::characters(const QString &ch)
{
    // Series characters
    if (handling_series)
        HandleSeries(ch);
    else
        HandleEpisode(ch);

    prev_element.clear();

    return true;
}

bool SeriesXMLHandler::error(const QXmlParseException &exception)
{
    qDebug() << exception.message();
    return true;
}

bool SeriesXMLHandler::fatalError(const QXmlParseException &exception)
{
    qDebug() << exception.message();
    return true;
}

void SeriesXMLHandler::parsingComplete(bool success)
{
    // We should have found all the mirrors
    emit SeriesXMLHandler::seriesReady();
}

