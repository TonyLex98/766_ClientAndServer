#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QObject>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QThread>

class UdpServer : public QObject
{
    Q_OBJECT
public:
    explicit UdpServer(QObject *parent = 0);

public slots:
    //Слот, который записывает в сокет датаграмму с параметрами из слайдеров:
    void slot_WriteParameters(qreal viewing_angle, qreal horizontal_shift, qreal vertical_shift);

private:
    //Создаю udp socket
    QUdpSocket *udp_socket;
};

#endif // UDPSERVER_H
