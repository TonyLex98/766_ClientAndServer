#ifndef SIGHT_H
#define SIGHT_H

#include <QGraphicsItem>
#include <QDebug>
#include <QPainter>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>

class Sight: public QGraphicsSvgItem
{
public:
    Sight();
    ~Sight();

    // Возращает список QPair<названий цветов прицела (на русском), путь к файлу svg с соответствующим цветом>
    QList<QPair<QString,QString>> Get_sight_colors();

public slots:
    // Устанавливает текущую картинку прицела по названию цвета (на русском):
    void slot_SetColorSight(QString color_name);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * widget);

private:
    QSvgRenderer *renderer;

    // Создаю список QPair<названий цветов прицела (на русском), путь к файлу svg с соответствующим цветом>
    QList<QPair<QString,QString>> sight_colors; //название цвета и путь к svg файлу

    // Заполняет список sight_colors
    void settingSightColour();

    // Размеры svg изображения с прицелом:
    int pictureWidth = 1024;
    int pictureHeight = 1024;

};

#endif // SIGHT_H
