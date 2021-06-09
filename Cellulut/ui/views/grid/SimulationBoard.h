#ifndef SIMULATIONBOARD_H
#define SIMULATIONBOARD_H

#include "main.h"
#include "models/Cell.h"
#include <QObject>
#include <QFrame>
#include <QPaintEvent>
#include <QPainter>

class SimulationBoard : public QFrame
{
    Q_OBJECT;
public:
    SimulationBoard(QWidget *parent = nullptr);
public slots:
    void changeGridSize(int newValue);
protected:
    void paintEvent(QPaintEvent *event) override;
private:
    int boardSize;
    int squareWidth(){return contentsRect().width() / boardSize;}
    int squareHeight(){return contentsRect().height() / boardSize;}
    void drawSquare(QPainter &painter, int x, int y);
    void clearBoard();
    vector<int> *board = 0;
};
#endif // SIMULATIONBOARD_H
