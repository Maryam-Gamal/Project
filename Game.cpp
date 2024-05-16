#include "Game.h"
#include <QApplication>
#include <QBrush>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMessageBox>
#include "Ball.h"
#include "Block.h"
#include "Level.h"
#include "Paddle.h"


// Constructor for the Game class
Game::Game()
    : levelRowsCount({3, 4, 5, 6, 7})  // Initialize the number of rows for each level
    , levelVelocity({-5, -6, -7, -8, -9}) // Initialize the velocity for each level
    , currentLevel(nullptr) // Initialize the current level pointer to nullptr
{


    // Display a start message box
    QMessageBox msgBox;
    msgBox.setWindowTitle("Start");
    msgBox.setIconPixmap(QPixmap(":/images/start.png"));
    msgBox.addButton("Start", QMessageBox::AcceptRole);
    QFont font;
    font.setPointSize(16); // Set the desired font size
    msgBox.setFont(font);
    msgBox.move(200, 300);
    msgBox.exec();

    // Initialize text items for displaying level, score, and health
    levelText = new QGraphicsTextItem();
    levelText->setDefaultTextColor(Qt::blue);
    QFont font1("times", 24, QFont::Bold);
    levelText->setFont(font1);
    levelText->setPos(350, 10);

    scoreText = new QGraphicsTextItem();
    scoreText->setFont(font1);
    scoreText->setDefaultTextColor(Qt::green);
    scoreText->setPos(30, 10);

    healthText = new QGraphicsTextItem();
    healthText->setFont(font1);
    healthText->setDefaultTextColor(Qt::red);
    healthText->setPos(30, 50);

    // Connect signals for game over and game won events
    connect(this, SIGNAL(gameOver()), this, SLOT(restartGame1()));
    connect(this, SIGNAL(gameWon()), this, SLOT(handleWinning()));

    startGame(0);  // Start the game with the first level
}


// Prepare the level for display
void Game::prepareLevel(int lvl)
{
    currentLevel->addToScene(levelText);
    currentLevel->addToScene(healthText);
    currentLevel->addToScene(scoreText);
    setLevel(lvl);
    setScore(currentLevel->getScore());
    setHealth(currentLevel->getHealth());
    connect(currentLevel, SIGNAL(healthChanged(int)), this, SLOT(changeHealth(int)));
    connect(currentLevel, SIGNAL(scoreChanged(int)), this, SLOT(changeScore(int)));
}


// Start the game with the specified level
void Game::startGame(int indx)
{
    if (currentLevel) {
        currentLevel->deleteLater();
    }
    currentLevel = nullptr;
    currentLevel = new Level(levelRowsCount[indx], levelVelocity[indx]);

    // Create and add a text item for the level
    prepareLevel(indx);
    currentLevel->show();
}


// Set the current level
void Game::setLevel(int lv)
{
    level = lv;
    levelText->setPlainText(QString("Level: ") + QString::number(level+1));
}

// Set the current score
void Game::setScore(int scr)
{
    scoreText->setPlainText(QString("Score: %1").arg(scr));
}

// Set the current health
void Game::setHealth(int hlth)
{
    healthText->setPlainText(QString("Health: %1").arg(hlth));
}


// Handle changes in health
void Game::changeHealth(int newHealth)
{
    setHealth(newHealth);
    if (newHealth == 0)
        emit gameOver();
}


// Handle changes in score
void Game::changeScore(int newScore)
{
    setScore(newScore);
    if (newScore == currentLevel->getTargetScore())
        emit gameWon();
}


// Handle winning the game
void Game::handleWinning()
{
    if(level == 0 || level == 1 || level == 2 || level == 3 ){
    // Display level completed message for levels 1 to 4
    QMessageBox msgBox;
    msgBox.setWindowTitle(QString("Level %1 Completed").arg(level + 1));
    msgBox.setIconPixmap(QPixmap(":/images/LevelUp.png"));
    msgBox.addButton("Next Level", QMessageBox::AcceptRole);
    QFont font;
    font.setPointSize(16);
    msgBox.setFont(font);
    msgBox.move(200, 300);
    msgBox.exec();
    }


    // Select Next Level or end game if max level is reached
    if (level == MAX_LEVEL_COUNT - 1){
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString("YOU WIN!"));
        msgBox.setIconPixmap(QPixmap(":/images/YouWin.png"));
        msgBox.addButton("Exit", QMessageBox::AcceptRole);
        QFont font;
        font.setPointSize(16);
        msgBox.setFont(font);
        msgBox.move(200, 300);
        msgBox.exec();
        exit(1);
    }
    else
        startGame(++level);  // Start the next level

}



// Restart the game when game over
void Game::restartGame1()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("GameOver");
    msgBox.setIconPixmap(QPixmap(":/images/gameover.png"));
    msgBox.addButton("Restart", QMessageBox::AcceptRole);
    QFont font;
    font.setPointSize(16); // Set the desired font size
    msgBox.setFont(font);
    msgBox.move(250, 350);
    msgBox.exec();

    currentLevel->deleteLater();
    //currentLevel = nullptr;
    startGame(0);  // Restart the game with the first level
}

Game::~Game() {}


