#ifndef NETXMLHANDLER_H
#define NETXMLHANDLER_H

#include <QXmlDefaultHandler>

class NetXMLHandler : public QObject, public QXmlDefaultHandler
{
    Q_OBJECT

public:
    NetXMLHandler();
    
signals:
    
public slots:
    void XMLReady();
};

#endif // NETXMLHANDLER_H
