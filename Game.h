#ifndef GAME_H
#define GAME_H
#include <QObject>
#include <QWidget>
#include <QVector>
#include "Level.h"

const int MAX_LEVEL_COUNT = 5;

class Game: public QObject
{    
    Q_OBJECT
public:
    Game();
    ~Game();
    void startGame(int indx);
private:
    void prepareLevel(int lvl);
    void setLevel(int level);
    void setHealth(int hlth);
    void setScore(int scr);

private slots:
    void restartGame1();
    void changeHealth(int newHealth);
    void changeScore(int newScore);
    void handleWinning();
signals:
    void gameOver();
    void gameWon();

public:
    Level* currentLevel;
    int level = 0;
    QGraphicsTextItem* levelText;
    QGraphicsTextItem* scoreText;
    QGraphicsTextItem* healthText;
    int levelRowsCount[MAX_LEVEL_COUNT];
    double levelVelocity[MAX_LEVEL_COUNT];
};
#endif // GAME_H
