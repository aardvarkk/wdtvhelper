#include <QDebug>

#include "mirrorsxmlhandler.h"

bool MirrorsXMLHandler::startElement(QString const& namespaceURI,  QString const& localName, QString const& qName, QXmlAttributes const& atts)
{
    qDebug() << "Found element " << qName;
    // Attributes
    for (int i = 0; i < atts.length(); ++i)
        qDebug() << "Attribute " << i << " has qName " << atts.qName(i) << " and value " << atts.value(i);
    prev_element = qName;
    return true;
}

bool MirrorsXMLHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    qDebug() << "Finished element " << qName;

    if (!qName.compare("Mirror"))
        mirrors.push_back(current_mirror);

    return true;
}

bool MirrorsXMLHandler::characters(const QString &ch)
{
    qDebug() << "Found characters " << ch;

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

bool MirrorsXMLHandler::startEntity(const QString &name)
{
    qDebug() << "Found entity " << name;
    return true;
}

bool MirrorsXMLHandler::startDTD(const QString &name, const QString &publicId, const QString &systemId)
{
    qDebug() << "Found DTD with name " << name;
    return true;
}

bool MirrorsXMLHandler::internalEntityDecl(const QString &name, const QString &value)
{
    qDebug() << "Internal entity with name " << name << " has value " << value;
    return true;
}

