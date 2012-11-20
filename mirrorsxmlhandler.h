#ifndef MIRRORSXMLPARSER_H
#define MIRRORSXMLPARSER_H

#include <QVector>

#include "netxmlhandler.h"
#include "mirror.h"

class MirrorsXMLHandler: public NetXMLHandler
{
    Q_OBJECT

public:
    MirrorsXMLHandler() {}
    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
    bool characters(const QString &ch);

    // accesors
    QVector<Mirror> getMirrors() { return mirrors; }

protected:
    virtual void parsingComplete(bool success);

signals:
    void mirrorsReady();
    
private:
    QString prev_element;
    Mirror current_mirror;
    QVector<Mirror> mirrors;
};

#endif // MIRRORSXMLPARSER_H
