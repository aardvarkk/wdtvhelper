#include <QDebug>

#include "mirrorsxmlhandler.h"

MirrorsXMLHandler::MirrorsXMLHandler()
{
    qDebug("I'm alive!");
}

bool MirrorsXMLHandler::startElement(QString const& namespaceURI,  QString const& localName, QString const& qName, QXmlAttributes const& atts)
{
    QString out;
    out += "Found element ";
    out += qName;

    qDebug() << out;
    return true;
}
