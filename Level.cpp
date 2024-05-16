#include "Level.h"


// Constructor for Level class
Level::Level(int rowsCount, double ballBaseVelocity)
{
    // Create a new QGraphicsScene for the level
    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,600,800);
    setBackgroundBrush(QBrush(QImage(":/images/background 4.jpg"))); // Set the background brush
    setScene(scene);  // Set the scene for the view
    // Disable horizontal and vertical scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(600,800); // Set fixed size for the view


    // Create the grid of blocks for the level
    BlocksGrid(rowsCount);

    // Create the ball and paddle for the level
    ball = new Ball(ballBaseVelocity, this);
    paddle = new Paddle(this);

    // Add the ball and paddle to the scene
    addToScene(ball);
    addToScene(paddle);

    // Initialize health and score
    health = 3;
    score = 0;

    // Connect signals from the ball to slots in the level
    connect(ball, SIGNAL(outOfReach()), this, SLOT(ballOutOfReach()));
    connect(ball, SIGNAL(blockHit(int)), this, SLOT(blockHit(int)));

    // Allow the paddle to receive keyboard events
    paddle->grabKeyboard();
}



//Ghada Ismail
// Create a grid of blocks for each level based on the rowsCount
void Level::BlocksGrid(int rowsCount)
{

    const int numColumns = 6;
    const int blockWidth = 80;
    const int blockHeight = 25;
    const int startY = 190;
    const int startX = 48;

    targetScore = 0;  // Initialize target score for the level

    // Loop to create rows of blocks
    for (int row = 0; row < rowsCount; ++row) {
        // Loop to create columns of blocks
        for (int col = 0; col < numColumns; ++col) {
            int x = startX + col * (blockWidth /*+ 5*/);
            int y = startY + row * (blockHeight /*+ 5*/);
            QColor color = Qt::blue;


            // Assign a color based on the row index
            switch (row) {
            case 0:
                color = Qt::magenta;
                break;
            case 1:
                color = Qt::cyan;
                break;
            case 2:
                color = Qt::yellow;
                break;
            case 3:
                color = Qt::gray;
                break;
            case 4:
                color = Qt::red;
                break;
            case 5:
                color = Qt::green;
                break;
            // Add more cases for additional rows with different colors
            default:
                color = Qt::blue;
                break;
            }

            // Construct a block with x, and y position, and the corresponding color
            block = new Block(x,y,color, this);
            targetScore += block->getScore(); // Update the target score
            scene->addItem(block); // Add the block to the scene
        }
    }
}


// Slot called when the ball goes out of reach: the health decreases by one
void Level::ballOutOfReach()
{
    health -=1;
    emit healthChanged(health);
}


// Slot called when a block is hit by the ball
void Level::blockHit(int scoreOfBlock)
{
    score += scoreOfBlock;  // Increase score by the score of the block (1)
    emit scoreChanged(score); // Emit signal to update score in the screen
}


// Get the target score for the level
int Level::getTargetScore() { return targetScore; }

// Get the current score for the level
int Level::getScore() { return score; }

// Get the current health for the level
int Level::getHealth() { return health; }
