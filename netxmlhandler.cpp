#include <QtNetwork>

#include "netxmlhandler.h"

NetXMLHandler::NetXMLHandler()
{
}

void NetXMLHandler::XMLReady()
{
    // this signal is sent by QNetworkReply
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    // Lets print the HTTP GET response.
    QByteArray ba = reply->readAll();

    // Done with the reply
    delete reply;

    // Create XML from it
    QBuffer buffer(&ba);

    // Parse it
    QXmlInputSource source(&buffer);
    QXmlSimpleReader reader;
    reader.setContentHandler(this);
    bool success = reader.parse(source);

    // Mention to our children that we're done parsing
    parsingComplete(success);
}
