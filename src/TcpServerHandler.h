#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class TcpServerHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(quint16 port READ getPort WRITE setPort NOTIFY portChanged)

public:
    explicit TcpServerHandler(quint16 port, QObject* parent = nullptr);
    ~TcpServerHandler();

    Q_INVOKABLE bool startServer();
    Q_INVOKABLE void stopServer();
    Q_INVOKABLE void restartServer();

    void setPort(quint16 port) noexcept;
    quint16 getPort() const noexcept;

signals:
    void serviceDataChanged(const QString&);
    void readyReadDataChanged(const QByteArray&);
    void portChanged();

private slots:
    void newConnection();
    void readyRead();

private:
    QTcpServer* _tcpServer;
    QVector<QTcpSocket*> _clients;
    QString _serviceMessage;

    quint16 _port = 0;
};
