#ifndef PADDLE_H
#define PADDLE_H

#include<QObject>
#include<QGraphicsRectItem>

class Paddle:public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Paddle(QObject *parent = nullptr);
    void keyPressEvent(QKeyEvent*event);
    double paddleCenterX();
};
#endif // PADDLE_H
