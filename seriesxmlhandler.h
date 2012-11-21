#ifndef SERIESXMLPARSER_H
#define SERIESXMLPARSER_H

#include <QVector>

#include "netxmlhandler.h"
#include "episode.h"
#include "series.h"

class SeriesXMLHandler: public NetXMLHandler
{
    Q_OBJECT

public:
    SeriesXMLHandler() : handling_series(true) {}
    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
    bool characters(const QString &ch);

    bool error(const QXmlParseException &exception);
    bool fatalError(const QXmlParseException &exception);

    void clear();

    // accesors
    Series getSeries() { return series; }
    QVector<Episode> getEpisodes() { return episodes; }

protected:
    virtual void parsingComplete(bool success);

signals:
    void seriesReady();
    
private:

    void HandleSeries(QString const& ch);
    void HandleEpisode(QString const& ch);

    QString prev_element;

    // switches once we go from series to episodes
    bool handling_series;

    Series current_series;
    Episode current_episode;

    Series series;
    QVector<Episode> episodes;
};

#endif // SERIESXMLPARSER_H
