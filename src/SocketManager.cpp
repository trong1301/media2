// 2W includes
#include "include/SocketManager.h"
#include "include/IndicatorIcon.h"
#include "include/MagicNumbers.h"

// Qt includes
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

SocketManager::SocketManager(QObject *parent)
    : QObject(parent)
    , LOCAL_IP_SOCKET("127.0.0.1")
    , LOCAL_PORT_SOCKET(7777)
    , m_socket{std::make_shared<QTcpSocket>(this)}
    , RECONNECT_SLEEP_TIME(2000)
{

    // Signal to reconnect after a time
    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);
    m_timer->setInterval(RECONNECT_SLEEP_TIME);
    connect(m_timer, &QTimer::timeout, this, &SocketManager::Reconnect);

    connect(m_socket.get(), &QTcpSocket::connected,this, &SocketManager::connected);
    connect(m_socket.get(), &QTcpSocket::disconnected,this, &SocketManager::disconnected);
    connect(m_socket.get(), &QTcpSocket::bytesWritten,this, [&](qint64 bytes){
        qDebug() << bytes << " bytes written...";
    });
    connect(m_socket.get(), &QTcpSocket::readyRead,this, &SocketManager::readyRead);
}

SocketManager::~SocketManager()
{
    disconnect(m_socket.get());
    disconnect(m_timer);
}

void SocketManager::doConnect()
{
    qDebug() << "Connecting to: " << LOCAL_IP_SOCKET << ":" << LOCAL_PORT_SOCKET;

    // Make use of Reconnect() to make sure if app could not connect to server
    // It will be retried as the same as lost the connection
    m_timer->start();
}

void SocketManager::connected()
{
    qDebug() << "Connected to: " << LOCAL_IP_SOCKET << ":" << LOCAL_PORT_SOCKET;
    m_socket->write("Hello from 2W");
}

void SocketManager::disconnected()
{
    qDebug() << "Disconnected from: " << LOCAL_IP_SOCKET << ":" << LOCAL_PORT_SOCKET;
    m_timer->start();
}

void SocketManager::Reconnect()
{
    qDebug() << "Trying re-connecting to " << LOCAL_IP_SOCKET << ":" << LOCAL_PORT_SOCKET;
    m_socket->connectToHost(LOCAL_IP_SOCKET, LOCAL_PORT_SOCKET);

    // Wait...
    if(!m_socket->waitForConnected(5000))
    {
        qDebug() << "Error: " << m_socket->errorString();
    }
    else
    {
        m_timer->stop();
    }
}

void SocketManager::readyRead()
{
    QString data = m_socket->readAll();
    // qDebug() << "Reading from socket: " << data;

    QJsonDocument jsonDocument = QJsonDocument::fromJson(data.toUtf8());
    QJsonValue turn_left = jsonDocument.object().value("turn_left");
    QJsonValue turn_right = jsonDocument.object().value("turn_right");
    QJsonValue head_light = jsonDocument.object().value("head_light");

    TwoWheelsTypes::Indicators indicators;
    if(!turn_left.isUndefined())
    {
        indicators.turn_left = turn_left.toInt();
    }

    if(!turn_right.isUndefined())
    {
        indicators.turn_right = turn_right.toInt();
    }

    if(!head_light.isUndefined())
    {
        indicators.head_light = head_light.toInt();
    }

    emit onIndicatorsDataStructureChanged(indicators);
}

