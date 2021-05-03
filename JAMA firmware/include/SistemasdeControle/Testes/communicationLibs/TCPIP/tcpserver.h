///
/// Created by Igorfel 20/04/16
/// It is Necessery to include QT       += network \ at the *.pro archive.
///
#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <stdlib.h>
#include <iostream>
#include <QObject>
#include <QtNetwork>
#include <QTcpServer>
#include <QTcpSocket>

class TCPServer : public QObject
{
    Q_OBJECT

public:
   explicit TCPServer(QObject *parent = 0);
   ~TCPServer();
    void writeData(const char*);

    QString dataReceived();
    long int getGate();
    QString getIpAddress();
//    ~TcpServer();
public slots:
    void sessionOpened();
    void update();
    void newClient();
    void read();

signals:
    void hasReadData();

private:
  QString bytesReaded;
  QString ipAddress;
  long int Porta;
  QTcpServer *tcpServer;
  QTcpSocket *clientConnection;
  QNetworkSession *networkSession;
};

#endif // TCPSERVER_H
