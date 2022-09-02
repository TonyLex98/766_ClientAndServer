#include "UdpClient.h"

UdpClient::UdpClient(QObject *parent) : QObject(parent)
{
    udp_socet = new QUdpSocket(this);
    udp_socet->bind(QHostAddress::LocalHost,1111);
    connect(udp_socet, &QUdpSocket::readyRead,this, &UdpClient::ReadingData);
}

void UdpClient::ReadingData()
{
    qDebug() << "ReadingData = "<<QThread::currentThreadId();
    qreal viewing_angle = 0;
    qreal horizontal_shift = 0;
    qreal vertical_shift = 0;

    QHostAddress sender;
    quint16 senderPort;
    while(udp_socet->hasPendingDatagrams()){
        QByteArray datagram;
        datagram.resize(udp_socet->pendingDatagramSize());
        udp_socet->readDatagram(datagram.data(),datagram.size(),&sender, &senderPort);

        QStringList qsl_parameters;
        qsl_parameters = QString(datagram).split('\t');

        if(qsl_parameters.size() == 3){

            for(auto param:qsl_parameters){

                QStringList qsl_param;
                qsl_param= param.split(":");

                if(qsl_param.size()==2){
                    if(qsl_param.at(0)=="viewing_angle"){
                        viewing_angle = qsl_param.at(1).toDouble();
                    }
                    else if(qsl_param.at(0)=="horizontal_shift"){
                        horizontal_shift = qsl_param.at(1).toDouble();
                    }
                    else if(qsl_param.at(0)=="vertical_shift"){
                        vertical_shift = qsl_param.at(1).toDouble();
                    }
                }
            }
        }
    }

    emit signal_ParametersFromServer(viewing_angle,horizontal_shift,vertical_shift);

}
