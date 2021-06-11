#include "SimulationBoard.h"

SimulationBoard::SimulationBoard(QWidget *parent) : QFrame(parent)
{
    setFrameStyle(QFrame::Panel|QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    setFixedHeight(400);
    setFixedWidth(400);
    isInConfigurationMode=true;

    qInfo() << "SimulationBoard::SimulationBoard - constructor";
}

SimulationBoard::~SimulationBoard()
{
    qInfo() << "SimulationBoard::~SimulationBoard - destructor";
}


void SimulationBoard::refreshGrid(){
    update();
}

void SimulationBoard::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);
    QPainter painter(this);
    QRect rect=contentsRect();

    int gridSize = Grid::getGrid()->getSize();
    map<string,Cell*> *cells = Grid::getGrid()->getCells();

    int boardTop = rect.bottom() - gridSize*squareSize();

    for(unsigned int i=0; i < cells->size(); i++){
        int cellX = i%gridSize;
        int cellY = i/gridSize;
        Cell *cell = cells->at(Cell::getHashFromPos(cellX, cellY));
        QString color = QString::fromStdString(cell->getState()->getColor());
        drawSquare(painter, rect.left() + cellX * squareSize(),
                   boardTop + cellY * squareSize(), color);
    }
}

void SimulationBoard::mousePressEvent(QMouseEvent *event){

    int gridSize = Grid::getGrid()->getSize();
    map<string,Cell*> *cells = Grid::getGrid()->getCells();

    if(!isInConfigurationMode){
        qInfo() << "SimulationBoard::mousePressEvent - not in configuration mode, ignore click event";
        return;
    }

    int clickPosX = event->pos().x();
    int clickPosY = event->pos().y();

    // Check if click is not outside the grid
    int gridMaxXorY = this->squareSize()*gridSize;
    int gridMinY = contentsRect().bottom() - gridSize*squareSize();

    if(clickPosX > gridMaxXorY || clickPosY > gridMinY+gridMaxXorY || clickPosY < gridMinY){
        qInfo() << "SimulationBoard::mousePressEvent - click outside of the grid, ignore click event";
        return;
    }

    // Get clicked cell hash
    int cellX = clickPosX / this->squareSize();
    int cellY= (clickPosY-gridMinY) / this->squareSize();
    string cellHash = Cell::getHashFromPos(cellX, cellY);

    // Change cell state
    Cell *cell = cells->at(cellHash);
    State *state = cell->getState();
    int stateIndex = state->getIndex();
    vector<State*> *listOfStates = Automate::getAutomate()->getModel()->getListStates();
    int nextStateIndex = stateIndex + 1 < listOfStates->size() ? stateIndex+1 : 0;
    cell->setState(listOfStates->at(nextStateIndex));
    update();
    emit initialConfigurationChanged();
}

void SimulationBoard::drawSquare(QPainter &painter, int x, int y, QString colorAsString){
    QColor color(colorAsString);
    painter.fillRect(x + 1, y + 1, squareSize() - 2, squareSize() - 2,
                     color);
    painter.setPen(color.lighter());
    painter.drawLine(x, y + squareSize() - 1, x, y);
    painter.drawLine(x, y, x + squareSize() - 1, y);

    painter.setPen(color.darker());
    painter.drawLine(x + 1, y + squareSize() - 1,
                     x + squareSize() - 1, y + squareSize() - 1);
    painter.drawLine(x + squareSize() - 1, y + squareSize() - 1,
                     x + squareSize() - 1, y + 1);
}
