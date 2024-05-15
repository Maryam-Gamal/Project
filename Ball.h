#ifndef BALL_H
#define BALL_H
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QObject>


class Ball : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    Ball(double baseVelocity, QObject *parent = nullptr);
    ~Ball();
    double getCenterX() const;

private:
    void reverseVelocity();
    void handlePaddleCollision();
    void handleBlockCollision();

public slots:
    void move();
    void reset();

signals:
    void outOfReach();
    void blockHit(int scoreOfBlock);

private:
    double xvelocity;
    double yvelocity;
    double baseVelocity;
};

#endif // BALL_H
