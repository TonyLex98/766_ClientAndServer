#include "Sight.h"

Sight::Sight()
{
    renderer = new QSvgRenderer();

    // Заполняю список цветов и путей к svg изображениям:
    settingSightColour();

    // Устанавливаем красный цвет прицела:
    this->slot_SetColorSight("Красный");
}

Sight::~Sight()
{
    delete renderer;
}

QList<QPair<QString, QString> > Sight::Get_sight_colors()
{
    return sight_colors;
}

void Sight::slot_SetColorSight(QString color_name)
{
    for(auto color:sight_colors){
        if(color.first == color_name){
            renderer->load(color.second);
            this->setSharedRenderer(renderer);
            return;
        }
    }
}


QRectF Sight::boundingRect() const
{
    return QRectF(-pictureWidth/2,-pictureHeight/2,
                  pictureWidth,pictureHeight);
}

void Sight::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    renderer->render(painter, boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}




void Sight::settingSightColour()
{
    QPair<QString,QString> color;

    color.first = "Красный";
    color.second = ":/Images/svg/crosshair red.svg";
    sight_colors.append(color);

    color.first = "Черный";
    color.second = ":/Images/svg/crosshair black.svg";
    sight_colors.append(color);
}

