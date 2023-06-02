#ifndef SOCKETMANAGER_H
#define SOCKETMANAGER_H

// C++ includes
#include <memory>

// Qt includes
#include <QObject>
#include <QDebug>
#include <QTcpSocket>
#include <QTimer>

// 2W includes
#include "MagicNumbers.h"

class SocketManager : public QObject
{
    Q_OBJECT
public:
    //!
    //! \brief SocketManager
    //! \param parent
    //!
    explicit SocketManager(QObject *parent = nullptr);
    ~SocketManager();

    //!
    //! \brief doConnect
    //!
    void doConnect();

    //!
    //! \brief connected
    //!
    void connected();

    //!
    //! \brief disconnected
    //!
    void disconnected();

    //!
    //! \brief bytesWritten
    //! \param bytes
    //!
    void bytesWritten(qint64 bytes);

    //!
    //! \brief readyRead
    //!
    void readyRead();

    //!
    //! \brief Reconnect
    //!
    void Reconnect();

signals:
    //!
    //! \brief onIndicatorsDataStructureChanged, emit indicator status which read from GPIO sent via socket
    //!
    void onIndicatorsDataStructureChanged(const TwoWheelsTypes::Indicators&);

private:
    //!
    //! \brief LOCAL_IP_SOCKET
    //!
    const QString LOCAL_IP_SOCKET;

    //!
    //! \brief LOCAL_PORT_SOCKET
    //!
    const uint16_t LOCAL_PORT_SOCKET;

    //!
    //! \brief socket
    //!
    std::shared_ptr<QTcpSocket> m_socket;

    //!
    //! \brief m_isDisconnected
    //!
    bool m_isDisconnected;

    //!
    //! \brief m_timer stores the timer to trigger after a time to reconnect socket server
    //!
    QTimer* m_timer;

    //!
    //! \brief RECONNECT_SLEEP_TIME
    //!
    const uint16_t RECONNECT_SLEEP_TIME;
};

#endif // SOCKETMANAGER_H
