#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QObject>

class Block : public QObject, public QGraphicsRectItem {
    Q_OBJECT
public:
    Block(int x, int y, QColor color, QObject* parent = nullptr); // Constructor
    int getScore() { return 1;}
private:
    int x;
    int y;
    QColor color;

};

#endif // BLOCK_H
