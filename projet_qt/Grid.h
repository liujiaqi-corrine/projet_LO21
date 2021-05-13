#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include "Cell.h"
#include "State.h"
//#include "Simulateur.h"

#include <string>

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFormLayout>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QIntValidator>

class Grid : public QWidget
{
    Q_OBJECT
    protected :
        unsigned int length=0;
        unsigned int width=0;

        Cell** listCells;

        QIntValidator* zeroOneValidator;
        QVBoxLayout* couche;
        QTableWidget* tableWidget;

    public :
        explicit Grid(QWidget* parent = nullptr);
        ~Grid() = default;

        unsigned int getLength() const;
        unsigned int getWidth() const;
        Cell** getlistCells() const;

        void setlistCells(Cell** _listCells);
        void setLength(unsigned int _length);
        void setWidth(unsigned int _width);

        void afficher_1_etat (Grid g);



};

#endif // GRID_H_INCLUDED
