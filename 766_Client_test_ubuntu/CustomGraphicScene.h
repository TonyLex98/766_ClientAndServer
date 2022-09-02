#ifndef CUSTOMGRAPHICSCENE_H
#define CUSTOMGRAPHICSCENE_H

#include <QGraphicsScene>
#include <Sight.h>
#include <QDebug>
#include <QGraphicsLineItem>
#include <QPoint>

class CustomGraphicScene: public QGraphicsScene
{
    Q_OBJECT
public:
    CustomGraphicScene();
    ~CustomGraphicScene();

    // Метод для установки изначальных размеров graphicsView:
    void setStartgraphicsViewSize(QSize start_gv_size);

    Sight *sight;

public slots:
    // Слот, который принимает параметры от сервера через сетевую часть приложения (из другого потока)
    void slot_ParametersFromServer(qreal viewing_angle, qreal horizontal_shift, qreal vertical_shift);

    // Слот, который срабатывает, когда изменился размер виджета (принимает сигнал со значением размера graphicsView):
    void slot_GraphicsViewNewSize(QSize size);

private:
    // Метод производит расчет параметра масштабирования относительно угла обзора
    qreal calculate_current_viewing_angle_scale(qreal angle);

    // Метод пересчета координаты из локальной системы координат x,y [-1,1]... в систему координат графической сцены:
    QPointF calculate_fromLocalToScene(qreal x, qreal y);

    // начальный и текущий размеры graphicsView:
    QSize start_graphicsView_size;
    QSize current_graphicsView_size;

    // Размер зеленого перекрестия:
    qreal cross_size = 100;

    // Начальный масштаб прицела (1024 на 1024 очень много, поэтому уменьшил)
    qreal start_sight_scale = 0.1;

    // Текущие координаты прицела на сцене:
    qreal current_x_sight = 0;
    qreal current_y_sight = 0;

    //начальный горизонтальный угол обзора в градусах
    qreal start_viewing_angle = 2;

    // Текущее значение масштаба зависящее от угла обзора
    qreal current_viewing_angle_scale = 1;

    // Масштаб, зависящий от размера виджета
    qreal widget_scale = 1.0;

    // Максимальные и минимальные значения локальных координат:
    qreal x_min_local = -1;
    qreal x_max_local = 1;
    qreal y_min_local = -1;
    qreal y_max_local = 1;

};

#endif // CUSTOMGRAPHICSCENE_H
