#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include "Grid.h"
#include "Model.h"
#include "Library.h"

class Automate : public QWidget
{
    public:
    Automate();

    private:
    QPushButton *b_library;
    QPushButton *b_voisinage;
    Grid* grille;
    Model* model;
    Library* lib;

    //Dialogue Modele
    QDialog* infos;
    QLineEdit *nom;
    QSpinBox *nb;
    int added;
    QPushButton *color;
    QColor* couleur;
    QLineEdit *label;
    QComboBox *list;


    public slots :
        void defineModel();
        void defineStates();
        void defineColor();
        void defineSurrounding();
        void drawSurrounding();
        void displaySurrounding();
        void chooseModel();
        void selectModel();
};







#endif // AUTOMATE_H
