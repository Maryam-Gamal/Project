#ifndef LEVEL_H
#define LEVEL_H
#include <QGraphicsView>
#include "Ball.h"
#include "Block.h"
#include "Paddle.h"


class Level : public QGraphicsView
{
    Q_OBJECT
public:
    Level(int rowsCount, double ballBaseVelocity);
    void addToScene(QGraphicsItem* item) { scene->addItem(item); }
    int getTargetScore();
    int getScore();
    int getHealth();

private:
    void BlocksGrid(int rowsCount);

private slots:
    void ballOutOfReach();
    void blockHit(int scoreOfBlock);

signals:
    void healthChanged(int health);
    void scoreChanged(int score);

private:
    QGraphicsScene *scene;
    Ball *ball;
    Paddle *paddle;
    Block *block;
    int score;
    int health;
    int targetScore;
};
#endif // LEVEL_H
