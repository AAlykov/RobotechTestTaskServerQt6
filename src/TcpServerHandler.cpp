#include "TcpServerHandler.h"

TcpServerHandler::TcpServerHandler(quint16 port, QObject* parent)
    : QObject{parent}
    , _port(port)
    , _tcpServer(new QTcpServer(this))
{
    connect(_tcpServer, &QTcpServer::newConnection, this, &TcpServerHandler::newConnection);
}

bool TcpServerHandler::startServer()
{
    if (!_tcpServer->listen(QHostAddress::Any, _port))
    {
        emit serviceDataChanged("Server could not start: " + _tcpServer->errorString());
        qCritical() << "Server could not start: " << _tcpServer->errorString();
        return false;
    }
    emit serviceDataChanged("Server started on port: " + QString::number(_port));
    qDebug() << "Server started on port: " << _port;

    return true;
}

void TcpServerHandler::stopServer()
{
    foreach (QTcpSocket* socket, _clients)
    {
        socket->close();
        socket->disconnectFromHost();
        socket->deleteLater();
    }

    _tcpServer->close();
    qDebug() << "Server stopped";
    emit serviceDataChanged("Server stopped");
}

void TcpServerHandler::restartServer()
{
    stopServer();
    startServer();
}

void TcpServerHandler::setPort(quint16 port) noexcept
{
    _port = port;
}

quint16 TcpServerHandler::getPort() const noexcept
{
    return _port;
}

void TcpServerHandler::newConnection()
{
    while (_tcpServer->hasPendingConnections())
    {
        QTcpSocket* socket = _tcpServer->nextPendingConnection();
        _clients << socket;

        connect(socket, &QTcpSocket::readyRead, this, &TcpServerHandler::readyRead);

        QString serviceData = tr("New connection: %1, port %2").arg(socket->peerAddress().toString()).arg(socket->peerPort());
        emit serviceDataChanged(serviceData);
        qDebug() << serviceData;
    }
}

void TcpServerHandler::readyRead()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    if (!socket)
        return;

    QByteArray buffer;
    buffer.resize(socket->bytesAvailable() + 1);
    buffer = socket->readAll();
    emit readyReadDataChanged(buffer);
}

TcpServerHandler::~TcpServerHandler()
{
    _tcpServer->deleteLater();
}
