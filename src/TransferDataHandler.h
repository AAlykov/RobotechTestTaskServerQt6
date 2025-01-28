#pragma once

#include "Pinger.h"
#include "TcpServerHandler.h"

#include <QObject>
#include <QDateTime>

class TransferDataHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList serviceDataList READ serviceData NOTIFY serviceDataChanged)
    Q_PROPERTY(QString transferData READ data NOTIFY dataChanged)
    Q_PROPERTY(QString transferDataHex READ dataHex NOTIFY dataHexChanged)
    Q_PROPERTY(QString transferDataPing READ dataPing NOTIFY dataPingChanged)

public:
    explicit TransferDataHandler(TcpServerHandler* tcpServerHandler, QObject* parent = nullptr);
    ~TransferDataHandler();

    QStringList serviceData() const noexcept;
    QString data() const noexcept;
    QString dataHex() const noexcept;
    QString dataPing() const noexcept;

    Q_INVOKABLE void ping(const QString&, const quint16 count, const quint16 size);

public slots:
    void handleDataChanged(const QByteArray&);
    void handleServiceDataChanged(const QString&);
    void handlePingDataChanged(const QString&);

signals:
    void dataChanged();
    void dataHexChanged();
    void dataPingChanged();
    void serviceDataChanged();

private:
    QStringList _serviceDataList;
    QString _transferData;
    QString _transferDataHex;
    QString _transferDataPing;
    TcpServerHandler* _tcpServerHandler;
    Pinger* _pinger;
};
