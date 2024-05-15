#include <QBrush>
#include <QGraphicsRectItem>
#include <QRect>
#include <QTimer>
#include "Block.h"
#include "Game.h"
#include "paddle.h"
#include "qmessagebox.h"


// Ghada Ismail
// Constructor for Ball class
Ball::Ball(double baseVelocity, QObject *parent)
    : QObject(parent), baseVelocity(baseVelocity)
{
    // Initialize ball properties
    reset();
    // Create a timer to move the ball
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move())); // Connect timer signal to move slot
    timer->start(15);
}

Ball::~Ball() {}


// Menna elSafty
// Get the center x-coordinate of the ball
double Ball::getCenterX() const
{
    return x() + rect().width() / 2;
}

// Menna elSafty
// Move the ball
void Ball::move()
{
    reverseVelocity();
    handlePaddleCollision();
    handleBlockCollision();
    moveBy(xvelocity, yvelocity);
}


// Reset the ball to its initial position and velocity
void Ball::reset()
{
    setRect(0, 0, 17, 17);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::red);
    setBrush(brush);
    xvelocity = 0;
    yvelocity = baseVelocity;
    setPos(300, 600);
}


//Ghada Ismail
// Reverse the ball's velocity if it hits the boundaries of the screen
void Ball::reverseVelocity()
{
    double screenwidth = 600;
    double screenheight = 800;

    if (mapToScene(boundingRect().topLeft()).x() <= 30) {
        xvelocity = -1 * xvelocity;
    }

    if (mapToScene(boundingRect().topRight()).x() >= screenwidth - 30) {
        xvelocity = -1 * xvelocity;
    }

    if (mapToScene(boundingRect().topLeft()).y() <= 140) {
        yvelocity = -1 * yvelocity;
    }

     // Reset the game if the ball goes out of bounds at the bottom
    if (mapToScene(boundingRect().bottomLeft()).y() >= screenheight) {
        emit outOfReach();  // Emit signal when ball goes out of reach
        reset();   // Reset the ball's position and velocity
    }
}

// Menna elSafty
// Handle collision with the paddle
void Ball::handlePaddleCollision()
{
    // Get list of colliding items
    QList<QGraphicsItem *> cItems = collidingItems();
    for (size_t i = 0, n = cItems.size(); i < n; ++i) {
        Paddle *paddle = dynamic_cast<Paddle *>( cItems[i]); // Check if the colliding item is the paddle
        if (paddle) {
            yvelocity = -1 * yvelocity; // Reverse y velocity

            // add to x velocity depending on where it hits the paddle
            double ballX = getCenterX();
            double paddleX = paddle->paddleCenterX();

            double dvx = ballX - paddleX;
            xvelocity = (xvelocity + dvx) / 15; // Adjust x velocity based on paddle position

            break;
        }
    }
}


//Ghada Ismail
// Handle collision with blocks
void Ball::handleBlockCollision()
{
     // Get list of colliding items
    QList<QGraphicsItem *> cItems = collidingItems();
    for (size_t i = 0, n = cItems.size(); i < n; ++i) {
        Block *block = dynamic_cast<Block *>(cItems[i]); // Check if the colliding item is a block
        if (block) {
        if (block) {
            double yPad = 15;
            double xPad = 15;
            double ballx = pos().x();
            double bally = pos().y();
            double blockx = block->pos().x();
            double blocky = block->pos().y();


            // Reverse y velocity if ball hits block vertically
            if ((bally > blocky + yPad && yvelocity < 0)
                || (blocky > bally + yPad && yvelocity > 0)) {
                yvelocity = -yvelocity;
            }

            // Reverse x velocity if ball hits block horizontally
            if ((ballx > blockx + xPad && xvelocity < 0)
                || (blockx > ballx + xPad && xvelocity > 0)) {
                xvelocity = -xvelocity;
            }

            emit blockHit(1);   // Emit signal when block is hit
            scene()->removeItem(block);  // Remove block from the scene


        }
    }
}
}
