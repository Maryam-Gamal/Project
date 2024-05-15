#include "Paddle.h"
#include <QBrush>
#include <QGraphicsScene>
#include <QKeyEvent>

Paddle::Paddle(QObject *parent)
    : QObject(parent)
{
    setRect(0, 0, 130, 15);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::white);
    setBrush(brush);
    setPos(250,750);
}

//Function to return the center x-coordinate of the paddle
double Paddle::paddleCenterX()
{
    return x() + rect().width() / 2;
}

// Event handler for key press events
void Paddle::keyPressEvent(QKeyEvent *event)
{
    // Move the paddle left when the left arrow key is pressed
    if (event->key() == Qt::Key_Left) {
        if (pos().x() > 0)   // Ensure paddle does not move out of bounds
            setPos(x() - 30, y());
    }// Move the paddle right when the right arrow key is pressed
    else if (event->key() == Qt::Key_Right) {
        if (pos().x() + 130 < 600)  // Ensure paddle does not move out of bounds
            setPos(x() + 30, y());
    }
}
