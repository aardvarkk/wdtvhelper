#include <QDebug>

#include "mirrorsxmlhandler.h"

bool MirrorsXMLHandler::startElement(QString const& namespaceURI,  QString const& localName, QString const& qName, QXmlAttributes const& atts)
{
    prev_element = qName;
    return true;
}

bool MirrorsXMLHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    if (!qName.compare("Mirror"))
        mirrors.push_back(current_mirror);

    return true;
}

bool MirrorsXMLHandler::characters(const QString &ch)
{
    if (!prev_element.compare("mirrorpath"))
    {
        current_mirror.url = QUrl(ch);
    }
    else if (!prev_element.compare("typemask"))
    {
        current_mirror.mirror_type = static_cast<Mirror::MirrorType>(ch.toInt());
    }

    // Reset
    prev_element = "";

    return true;
}

bool MirrorsXMLHandler::endDocument()
{
    // We should have found all the mirrors
    emit MirrorsXMLHandler::mirrorsReady();
    return true;
}

