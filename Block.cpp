#include "Block.h"
#include <QBrush>
#include <QGraphicsScene>

// Constructor for Block class
Block::Block(int x, int y, QColor color, QObject* parent): QObject(parent), QGraphicsRectItem() {
    // draw rect for the block
    setRect(x, y, 80, 25);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    setBrush(brush); // Set the brush color for the block

}
