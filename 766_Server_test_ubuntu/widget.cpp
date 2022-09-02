#include "widget.h"
#include "./ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    udp_server = new UdpServer();
    server_send_thread = new QThread(this);

    // Соединяю сигнал destroyed со слотом quit для закрытия потока:
    connect(this, &Widget::destroyed, server_send_thread, &QThread::quit);

    // Соединяю слот записи параметров через сокет и сигнал из виджета для передачи параметров в поток сетевой части
    connect(this, &Widget::signal_WriteParameters,udp_server, &UdpServer::slot_WriteParameters,Qt::QueuedConnection);

    // Закидываю сетевую часть приложения в поток:
    udp_server->moveToThread(server_send_thread);

    // Устанавливаю минимальные и максимальные значения соответствующих слайдеров
    ui->horizontalSlider_viewing_angle->setMinimum(num_steps_horizontal_slider*viewing_angle_min);
    ui->horizontalSlider_viewing_angle->setMaximum(num_steps_horizontal_slider*viewing_angle_max);

    ui->horizontalSlider_horizontal_shift->setMinimum(num_steps_horizontal_slider*horizontal_shift_min);
    ui->horizontalSlider_horizontal_shift->setMaximum(num_steps_horizontal_slider*horizontal_shift_max);

    ui->horizontalSlider_vertical_shift->setMinimum(num_steps_horizontal_slider*vertical_shift_min);
    ui->horizontalSlider_vertical_shift->setMaximum(num_steps_horizontal_slider*vertical_shift_max);

    // Запускаю поток
    server_send_thread->start();

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_send_clicked()
{
    qDebug() << "Server Widget = "<<QThread::currentThreadId();
    // Отправляю сигнал с параметрами в поток сетевой части приложения:
    emit signal_WriteParameters(viewing_angle,horizontal_shift,vertical_shift);
}

qreal Widget::get_right_value_from_slider(int value)
{
    return value/num_steps_horizontal_slider;
}

void Widget::on_horizontalSlider_viewing_angle_valueChanged(int value)
{
    viewing_angle = get_right_value_from_slider(value);
    ui->label_viewing_angle_value->setText(QString::number(viewing_angle));
}

void Widget::on_horizontalSlider_horizontal_shift_valueChanged(int value)
{

    horizontal_shift = get_right_value_from_slider(value);
    ui->label_horizontal_shift_value->setText(QString::number(horizontal_shift));
}


void Widget::on_horizontalSlider_vertical_shift_valueChanged(int value)
{
    vertical_shift = get_right_value_from_slider(value);
    ui->label_vertical_shift_value->setText(QString::number(vertical_shift));
}

