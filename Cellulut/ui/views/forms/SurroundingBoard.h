#ifndef SURROUNDINGBOARD_H
#define SURROUNDINGBOARD_H

#include "main.h"

class SurroundingBoard : public QFrame
{
    Q_OBJECT;
    public:
        SurroundingBoard(QWidget *parent = nullptr);
        ~SurroundingBoard();

        map<string, bool>* getBoard() const {return this->board;}
        int getBoardSize() const {return this->boardSize;}
        vector<bool> *getBoardAsVector();
    public slots:
        void changeBoardSize(QString newSize);
    protected:
        void paintEvent(QPaintEvent *pe) override;
        void mousePressEvent(QMouseEvent *event) override;
    private:
        int boardSize;
        map<string,bool> *board;
        void refreshGrid();
        string getHashFromPos(int posX, int posY) {return to_string(posX)+"-"+to_string(posY);}
        int squareSize(){return contentsRect().width() / this->boardSize;}
        void drawSquare(QPainter &painter, int x, int y, QString color);
};

#endif // SURROUNDINGBOARD_H
