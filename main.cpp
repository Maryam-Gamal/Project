#include <QApplication>
#include "Game.h"
#include <QMessageBox>
#include <QDebug>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);


    Game *game = new Game(); // Create a new Game object

    return a.exec();
}
