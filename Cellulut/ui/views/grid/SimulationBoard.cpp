#include "SimulationBoard.h"

SimulationBoard::SimulationBoard(QWidget *parent) : QFrame(parent)
{
    this->boardSize = MIN_GRID_SIZE;
    setFrameStyle(QFrame::Panel|QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    clearBoard();
}

void SimulationBoard::changeGridSize(int newValue){
    this->boardSize = newValue;
    update();
}

void SimulationBoard::clearBoard(){
    qInfo() << "SimulationBoard::clearBoard";
}

void SimulationBoard::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);
    QPainter painter(this);
    QRect rect=contentsRect();

    int boardTop = rect.bottom() - boardSize*squareHeight();

    for(int i=0; i < boardSize; ++i){
        for(int j = 0; j < boardSize; ++j){
            drawSquare(painter, rect.left() + j * squareWidth(),
                       boardTop + i * squareHeight());
        }
    }
}

void SimulationBoard::drawSquare(QPainter &painter, int x, int y){
    QColor color(0xFFFFFF);

    painter.fillRect(x + 1, y + 1, squareWidth() - 2, squareHeight() - 2,
                     color);

    painter.setPen(color.lighter());
    painter.drawLine(x, y + squareHeight() - 1, x, y);
    painter.drawLine(x, y, x + squareWidth() - 1, y);

    painter.setPen(color.darker());
    painter.drawLine(x + 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + squareHeight() - 1);
    painter.drawLine(x + squareWidth() - 1, y + squareHeight() - 1,
                     x + squareWidth() - 1, y + 1);
}
