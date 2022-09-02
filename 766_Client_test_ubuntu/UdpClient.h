#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QObject>
#include <QUdpSocket>
#include <QThread>

class UdpClient : public QObject
{
    Q_OBJECT
public:
    explicit UdpClient(QObject *parent = 0);

signals:
    void signal_ParametersFromServer(qreal viewing_angle, qreal horizontal_shift, qreal vertical_shift);

public slots:
    void ReadingData();

private:
    QUdpSocket *udp_socet;
};

#endif // UDPCLIENT_H
