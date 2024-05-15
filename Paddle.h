#ifndef PADDLE_H
#define PADDLE_H

#include<QObject>
#include<QGraphicsRectItem>

class Paddle:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Paddle(QGraphicsPixmapItem *parent = nullptr);
    void keyPressEvent(QKeyEvent*event);
    double paddleCenterX();
};

#endif // PADDLE_H
