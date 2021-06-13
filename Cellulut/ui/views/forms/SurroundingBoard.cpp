#include "SurroundingBoard.h"

SurroundingBoard::SurroundingBoard(QWidget *parent) : QFrame(parent)
{
    setFrameStyle(QFrame::Panel|QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    setFixedHeight(400);
    setFixedWidth(400);

    this->board = new map<string, bool>();
    this->changeBoardSize("1");

    //qInfo() << "SurroundingBoard::SurroundingBoard - constructor";
}

SurroundingBoard::~SurroundingBoard()
{
    //qInfo() << "SurroundingBoard::~SurroundingBoard - destructor";
}

void SurroundingBoard::changeBoardSize(QString newSizeAsStr){
    int newSize = newSizeAsStr.toInt();
    this->board->clear();
    this->boardSize = newSize*2+1;
    int medianIndex = boardSize/2;
    for(int i = 0; i < this->boardSize*this->boardSize; i++){
        int posX = i%this->boardSize;
        int posY = i/this->boardSize;
        bool interactionValue = false;
        if(posX == medianIndex && posY == medianIndex)
            interactionValue = true;

        this->board->insert({this->getHashFromPos(posX,posY),interactionValue});
    }
    this->refreshGrid();
}

void SurroundingBoard::refreshGrid(){
    update();
}

void SurroundingBoard::paintEvent(QPaintEvent *event){
    QFrame::paintEvent(event);
    QPainter painter(this);
    QRect rect=contentsRect();
    int boardTop = rect.bottom() - boardSize*squareSize();

    for(unsigned int i=0; i < this->boardSize*this->boardSize; i++){
        int posX = i%this->boardSize;
        int posY = i/this->boardSize;
        bool interactionValue= this->board->at(this->getHashFromPos(posX, posY));
        QString color = interactionValue ? "#000000" : "#FFFFFF";
        drawSquare(painter, rect.left() + posX * squareSize(),
                   boardTop + posY * squareSize(), color);
    }
}

void SurroundingBoard::drawSquare(QPainter &painter, int x, int y, QString colorAsString){
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

void SurroundingBoard::mousePressEvent(QMouseEvent *event){
    int clickPosX = event->pos().x();
    int clickPosY = event->pos().y();

    // Check if click is not outside the grid
    int gridMaxXorY = this->squareSize()*boardSize;
    int gridMinY = contentsRect().bottom() - boardSize*squareSize();

    if(clickPosX > gridMaxXorY || clickPosY > gridMinY+gridMaxXorY || clickPosY < gridMinY){
        qInfo() << "SurroundingBoard::mousePressEvent - click outside of the grid, ignore click event";
        return;
    }

    // Get clicked cell hash
    int cellX = clickPosX / this->squareSize();
    int cellY= (clickPosY-gridMinY) / this->squareSize();
    string cellHash = this->getHashFromPos(cellX, cellY);

    // Change interaction value
    bool interactionValue = this->board->at(cellHash);
    bool newInteractionValue = !interactionValue;
    this->board->erase(cellHash);
    this->board->insert({cellHash, newInteractionValue});
    update();
}

vector<bool> *SurroundingBoard::getBoardAsVector(){
    vector<bool> *result = new vector<bool>();
    for(int i = 0; i < this->boardSize*this->boardSize; i++){
        string hash = this->getHashFromPos(i%boardSize, i/boardSize);
        bool interactionValue = this->board->at(hash);
        result->push_back(interactionValue);
    }
    return result;
}
