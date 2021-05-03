#include "SistemasdeControle/headers/communicationLibs/TCPIP/tcpclient.h"

//START PUBLIC-----///////
TCPClient::TCPClient(QObject *parent): QObject(parent)
{
    registerSlots();
    Init();
}

TCPClient::TCPClient(QString address, quint16 port)
{
    registerSlots();
    Init();

    Connect2Host(address, port);
}

TCPClient::~TCPClient()
{
    DisconnectFromHost();
}

void TCPClient::Connect2Host(QString address, quint16 port)
{
    QHostAddress addr(address);
    socket.connectToHost(addr, port);
}

void TCPClient::DisconnectFromHost()
{
    socket.disconnectFromHost();
    socket.close();
}

//QTcpClient Client::getClient() {
//    return this->Client;
//}

bool TCPClient::isConneted()
{
    std::cout<<socket.errorString().toStdString();
    return this->hasConnection;
}

bool TCPClient::writeData(QString str)
{
    if(this->hasConnection)
    {
        socket.waitForConnected();
        socket.write(str.toStdString().c_str());
    }

    return socket.flush();
}

QString TCPClient::dataReceived()
{
    return this->bytesReaded;
}
//END PUBLIC------////////

//START PRIVATE-----/////////
void TCPClient::Init()
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

        this->networkSession = new QNetworkSession(config, this);
        connect(this->networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        this->networkSession->open();
    }
}

void TCPClient::registerSlots()
{
    connect(&socket, SIGNAL(connected()), this, SLOT(Awake()));
    connect(&socket, SIGNAL(readyRead()), this, SLOT(readData()));
}
//END PRIVATE-----///////////

//START SLOTS-----////////
void TCPClient::Awake()
{
    this->hasConnection = true;
    emit connectionSuccessful();
}

/*!
 * \brief     Client::readData
 *  \details   This function is triggered when the Client receives any data.
 */

void TCPClient::readData()
{
    char buffer[1024] = {0};
    unsigned sizeChar = socket.bytesAvailable();

    socket.read(buffer, sizeChar);
    this->bytesReaded.clear();

    for(unsigned i = 0; i < sizeChar; ++i){
        this->bytesReaded.append(QString::number((int) buffer[i]));
        if(i < sizeChar-1)
            this->bytesReaded.append(", ");
    }

    emit this->hasReadData();
}
