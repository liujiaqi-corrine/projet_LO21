#ifndef SIMULATIONBOARD_H
#define SIMULATIONBOARD_H

#include "main.h"
#include "models/Cell.h"
#include "models/State.h"
#include "models/Grid.h"
#include "models/Automate.h"

class SimulationBoard : public QFrame
{
    Q_OBJECT;
public:
    SimulationBoard(QWidget *parent = nullptr);
    ~SimulationBoard();
public slots:
    void refreshGrid();
protected:
    void paintEvent(QPaintEvent *pe) override;
    void mousePressEvent(QMouseEvent *event) override;
signals:
    void initialConfigurationChanged();
private:
    bool isInConfigurationMode;
    int squareSize(){return contentsRect().width() / Grid::getGrid()->getSize();}
    void drawSquare(QPainter &painter, int x, int y, QString colorAsString);
    void clearBoard();
};
#endif // SIMULATIONBOARD_H
