#include "Paddle.h"
#include<QGraphicsScene>
#include<QKeyEvent>

// Constructor for Paddle class
Paddle::Paddle(QGraphicsPixmapItem *parent)
{
    setPixmap(QPixmap(":/images/paddle.png")); // Set the pixmap for the paddle
}

//Function to return the center x-coordinate of the paddle
double Paddle::paddleCenterX(){
    return x() + pixmap().width() / 2;
}


// Event handler for key press events
void Paddle::keyPressEvent(QKeyEvent*event)
{
    // Move the paddle left when the left arrow key is pressed
     if(event->key()==Qt::Key_Left) // Ensure paddle does not move out of bounds
    {
        if(pos().x()>0)  // Ensure paddle does not move out of bounds
            setPos(x()-30,y());  // Move the paddle left by 30 units
    }
    // Move the paddle right when the right arrow key is pressed
    else if(event->key()==Qt::Key_Right)
    {
        if(pos().x()+100 < 600)  // Ensure paddle does not move out of bounds
            setPos(x()+30,y());  // Move the paddle right by 30 units
    }
}
