#ifndef MIRRORSXMLPARSER_H
#define MIRRORSXMLPARSER_H

#include "netxmlhandler.h"

class MirrorsXMLHandler: public NetXMLHandler
{
public:
    MirrorsXMLHandler();
    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);

signals:
    
public slots:
    
};

#endif // MIRRORSXMLPARSER_H
