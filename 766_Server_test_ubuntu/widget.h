#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <qdebug.h>
#include <UdpServer.h>
#include <QThread>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    // Слот кнопки дл отправки параметров
    void on_pushButton_send_clicked();

    // Слоты, которые срабатывают при изменении значений слайдеров:
    void on_horizontalSlider_viewing_angle_valueChanged(int value);
    void on_horizontalSlider_horizontal_shift_valueChanged(int value);
    void on_horizontalSlider_vertical_shift_valueChanged(int value);

signals:
    // Сигнал отправки параметров со слайдеров в поток отправки по udp:
    void signal_WriteParameters(qreal viewing_angle, qreal horizontal_shift, qreal vertical_shift);

private:
    // Метод возращает правильные значения со слайдеров:
    qreal get_right_value_from_slider(int value);

    Ui::Widget *ui;

    UdpServer *udp_server;

    // Создаю поток, в который буду отправлять udp_server:
    QThread *server_send_thread;

    // Колличество шагов на слайдере:
    qreal num_steps_horizontal_slider = 1000;

    // Передаваемые параметры:
    qreal viewing_angle = 2;
    qreal horizontal_shift = 0;
    qreal vertical_shift = 0;

    // Минимальные и максимальные размеры параметров:
    qreal viewing_angle_min = 2;
    qreal viewing_angle_max = 5;
    qreal horizontal_shift_min = -1;
    qreal horizontal_shift_max = 1;
    qreal vertical_shift_min = -1;
    qreal vertical_shift_max = 1;


};
#endif // WIDGET_H
