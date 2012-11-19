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
    bool startEntity(const QString &name);
    bool startDTD(const QString &name, const QString &publicId, const QString &systemId);
    bool internalEntityDecl(const QString &name, const QString &value);
    bool characters(const QString &ch);
    bool endDocument();

    // accesors
    QVector<Mirror> getMirrors() { return mirrors; }

signals:
    void mirrorsReady();
    
private:
    QString prev_element;
    Mirror current_mirror;
    QVector<Mirror> mirrors;
};

#endif // MIRRORSXMLPARSER_H
