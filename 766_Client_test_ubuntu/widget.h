#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>
#include <QPair>
#include <CustomGraphicScene.h>
#include <UdpClient.h>
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
    void on_comboBox_background_color_currentIndexChanged(int index);

    void on_comboBox_sight_color_currentTextChanged(const QString &arg1);

public slots:
    void slot_ParametersFromServer(qreal viewing_angle, qreal horizontal_shift, qreal vertical_shift);

protected:
    virtual void resizeEvent ( QResizeEvent * e);

signals:
    // Сигнал установки цвета прицела (передает название йвета на русском):
    void signal_SetColorSight(QString color);

    void signal_GraphicsViewNewSize(QSize size);

private:
    Ui::Widget *ui;

    CustomGraphicScene *custom_scene;

    UdpClient *udp_client;

    QThread *client_reciev_thread;

    // Список  QPair<название цвета на русском, соответствующее названию QColor>
    QList<QPair<QString,QColor>> background_colors;

    double ratioWidetoHeigh = (double)4/3;

    // Метод заполнения списка background_colors
    void settingBackgroundColour();

    // Метод заполнения названия цветов прицела в combobox
    void settingSightColorInCombobox();

    bool firstOpenResizeEvent = true;

};
#endif // WIDGET_H
