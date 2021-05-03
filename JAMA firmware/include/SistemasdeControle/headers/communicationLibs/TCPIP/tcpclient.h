///
/// Created by Igorfel 20/04/16
/// It is Necessery to include QT       += network \ at the *.pro archive.
///
#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <iostream>
#include <QtNetwork>
#include <QObject>
#include <QString>
#include <QTcpSocket>
#include <QHostAddress>

    class TCPClient: public QObject
    {
        Q_OBJECT
    public:
        explicit TCPClient  (QObject *parent = 0);
                 TCPClient  (QString address = "", quint16 port = 0);
                 ~TCPClient ();

        void Connect2Host(QString address, quint16 port);
        void DisconnectFromHost();

        bool writeData(QString str);
        bool isConneted();

        QString dataReceived();

    private:
        bool hasConnection;

        QTcpSocket socket;
        QString bytesReaded;
        QNetworkSession *networkSession;

        void Init();
        void registerSlots();

    signals:
        void hasReadData();
        void connectionSuccessful();

    private slots:
        void readData();
        void Awake();
    };


//#include "SistemasdeControle/src/communicationLibs/TCPIP/tcpclient.hpp"
#endif // TCPCLIENT_H
