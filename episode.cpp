#include <QXmlStreamWriter>

#include "episode.h"

Episode::Episode()
{
    id = 0;
    combined_episode = 0;
    combined_season = 0;
    dvd_chapter = 0;
    dvd_disc_id = 0;
    dvd_season = 0;
    ep_img_flag = 0;
    episode_number = 0;
    rating = 0;
    rating_count = 0;
    season_number = 0;
    absolute_number = 0;
    last_updated = 0;
    season_id = 0;
    series_id = 0;
}

void Episode::saveToWDTVXML(QDir const& dir, QString filename)
{
    // Make sure the directory exists
    if (!dir.exists()) return;

    // Create a file inside that directory
    QFile file(dir.absolutePath() + '/' + filename);

    // TODO: If it exists, just overwrite it for now...

    // Did it work?
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    // Open the XML stream
    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("details");

    stream.writeStartElement("id");
    stream.writeCharacters(QString::number(id));
    stream.writeEndElement();

    stream.writeStartElement("title");
    stream.writeCharacters(seasonString() + episodeString() + " " + episode_name);
    stream.writeEndElement();

    stream.writeStartElement("series_name");
    stream.writeCharacters(series.series_name);
    stream.writeEndElement();

//    stream.writeStartElement("mpaa");
//    stream.writeCharacters(ContentRating::toString(series.content_rating));
//    stream.writeEndElement();

    stream.writeStartElement("episode_name");
    stream.writeCharacters(episode_name);
    stream.writeEndElement();

    stream.writeStartElement("season_number");
    stream.writeCharacters(QString::number(season_number));
    stream.writeEndElement();

    stream.writeStartElement("episode_number");
    stream.writeCharacters(QString::number(episode_number));
    stream.writeEndElement();

    stream.writeStartElement("firstaired");
    stream.writeCharacters(first_aired.toString("yyyy-MM-dd"));
    stream.writeEndElement();

//    stream.writeStartElement("year");
//    stream.writeCharacters(QString::number(first_aired.year()));
//    stream.writeEndElement();

    stream.writeStartElement("genre");
    for (int i = 0; i < series.genres.size(); ++i)
    {
        if (i > 0) stream.writeCharacters("/");
        stream.writeCharacters(series.genres[i]);
    }
    stream.writeEndElement();

    stream.writeStartElement("runtime");
    stream.writeCharacters(QString::number(series.runtime));
    stream.writeEndElement();

    stream.writeStartElement("director");
    for (int i = 0; i < directors.size(); ++i)
    {
        if (i > 0) stream.writeCharacters("/");
        stream.writeCharacters(directors[i]);
    }
    stream.writeEndElement();

    stream.writeStartElement("actor");
    for (int i = 0; i < series.actors.size(); ++i)
    {
        if (i > 0) stream.writeCharacters("/");
        stream.writeCharacters(series.actors[i]);
    }

    for (int i = 0; i < guest_stars.size(); ++i)
    {
        if (i > 0) stream.writeCharacters("/");
        stream.writeCharacters(guest_stars[i]);
    }
    stream.writeEndElement();

//    stream.writeStartElement("plot");
//    stream.writeCharacters(overview);
//    stream.writeEndElement();

    stream.writeStartElement("overview");
    stream.writeCharacters(overview);
    stream.writeEndElement();

    stream.writeEndDocument();

    // We're done
    file.close();
}
