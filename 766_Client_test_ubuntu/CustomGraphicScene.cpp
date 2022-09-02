#include "CustomGraphicScene.h"

CustomGraphicScene::CustomGraphicScene()
{
    sight = new Sight();

    // Добавляю прицел на сцену
    this->addItem(sight);

    // Устанавливаю начальный масштаб и позицию прицела:
    sight->setScale(start_sight_scale);
    sight->setPos(current_x_sight,current_y_sight);


    // Добавляю зеленый крестик по середине:
    this->addLine(-cross_size/2,0,cross_size/2,0,QPen(Qt::green));
    this->addLine(0,-cross_size/2,0,cross_size/2,QPen(Qt::green));
}

CustomGraphicScene::~CustomGraphicScene()
{
    delete sight;
}

qreal CustomGraphicScene::calculate_current_viewing_angle_scale(qreal angle)
{
    // Определяю масштаб как отношение тангенсов половинного угла
    current_viewing_angle_scale = atan(M_PI*angle/180/2)/atan(M_PI*start_viewing_angle/180/2);
    return  current_viewing_angle_scale;
}

void CustomGraphicScene::setStartgraphicsViewSize(QSize start_gv_size)
{
    start_graphicsView_size = start_gv_size;
}

void CustomGraphicScene::slot_ParametersFromServer(qreal viewing_angle, qreal horizontal_shift, qreal vertical_shift)
{
    current_x_sight = horizontal_shift;
    current_y_sight = vertical_shift;

    current_viewing_angle_scale = calculate_current_viewing_angle_scale(viewing_angle);
    sight->setScale(current_viewing_angle_scale*widget_scale*start_sight_scale);
    sight->setPos(calculate_fromLocalToScene(current_x_sight,current_y_sight));

}

void CustomGraphicScene::slot_GraphicsViewNewSize(QSize size)
{
    current_graphicsView_size = size;

    // Устанавливаю новые границы сцены, чтобы отрисовка крестика всегда была по середине
    this->setSceneRect(-current_graphicsView_size.width()/2,-current_graphicsView_size.height()/2,current_graphicsView_size.width(),current_graphicsView_size.height());

    widget_scale = (double)current_graphicsView_size.width()/start_graphicsView_size.width();
    sight->setScale(current_viewing_angle_scale*widget_scale*start_sight_scale);
    sight->setPos(calculate_fromLocalToScene(current_x_sight,current_y_sight));
}

QPointF CustomGraphicScene::calculate_fromLocalToScene(qreal x, qreal y)
{
    return QPointF(this->width()*x/(x_max_local-x_min_local),this->height()*y/(y_max_local-y_min_local));
}
