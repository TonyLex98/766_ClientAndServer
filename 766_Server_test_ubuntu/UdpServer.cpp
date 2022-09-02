#include "UdpServer.h"

UdpServer::UdpServer(QObject *parent) : QObject(parent)
{
    udp_socket = new QUdpSocket(this);
}

void UdpServer::slot_WriteParameters(qreal viewing_angle, qreal horizontal_shift, qreal vertical_shift)
{
    qDebug() << "slot_WriteParameters = "<<QThread::currentThreadId();
    //Формирую отправляемую датаграмму:
    QString send_message;
    send_message.append("viewing_angle:"+QString::number(viewing_angle)+'\t');
    send_message.append("horizontal_shift:"+QString::number(horizontal_shift)+'\t');
    send_message.append("vertical_shift:"+QString::number(vertical_shift));

    //отправляю датаграмму:
    udp_socket->writeDatagram(send_message.toUtf8(),QHostAddress::LocalHost,1111);
}
