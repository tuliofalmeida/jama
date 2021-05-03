#include "SistemasdeControle/headers/communicationLibs/TCPIP/tcpserver.h"

TCPServer::TCPServer(QObject *parent):
    QObject(parent), tcpServer(0), networkSession(0)
{
    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));
        std::cout << "Abrindo a conexao";
        networkSession->open();
    } else {
        sessionOpened();
    }

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newClient()));
    //connect(clientConnection, SIGNAL(readyRead()), this,

//    QTimer *timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
//    timer->start(100);
}

void TCPServer::update()
{
    //write("123");
}

TCPServer::~TCPServer()
{
    delete clientConnection;
    delete tcpServer;
    delete networkSession;
//   if(clientConnection->isOpen())
//    clientConnection->disconnectFromHost();
//   clientConnection->close();
}

void TCPServer::sessionOpened()
{
    // Save the used configuration
    if (networkSession) {
        QNetworkConfiguration config = networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen()) {
        std::cout << "Unable to start the server: %1.";

        return;
    }
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    std::cout << "The server is running on\n\nIP: " << ipAddress.toStdString()
              <<"\nport: " << tcpServer->serverPort() << "\n\n";
    this->Porta = tcpServer->serverPort();
}

void TCPServer::newClient()
{
   clientConnection = tcpServer->nextPendingConnection();
   connect(clientConnection, SIGNAL(readyRead()), this, SLOT(read()));

    std::cout << "nova conexao\n";
}

void TCPServer::read()
{
    char buffer[1024] = {0};
    unsigned sizeChar = clientConnection->bytesAvailable();
    clientConnection->read(buffer, clientConnection->bytesAvailable());

    this->bytesReaded.clear();
    for(unsigned i = 0; i < sizeChar; ++i)
        this->bytesReaded.append(buffer[i]);

    emit this->hasReadData();
}

QString TCPServer::dataReceived()
{
    return this->bytesReaded;
}

void TCPServer::writeData(const char *dataToWrite)
{
    if(clientConnection->isOpen() && clientConnection->isWritable()){
        clientConnection->write(dataToWrite);
        clientConnection->flush();
    }
}

long int TCPServer::getGate(){
    return Porta;
}

QString TCPServer::getIpAddress(){
    return ipAddress;
}
