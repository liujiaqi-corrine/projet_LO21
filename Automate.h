#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QDialog>
#include "Grid.h"
#include "Model.h"

class Automate : public QWidget
{
    public:
    Automate();

    private:
    QPushButton *b_modele;
    QPushButton *b_voisinage;
    Grid* grille;
    Model* model;

    //Dialogue Modele
    QDialog* infos;
    QLineEdit *nom;
    QSpinBox *nb;
    int added;
    QPushButton *color;
    QColor* couleur;
    QLineEdit *label;


    public slots :
        void defineModel();
        void defineStates();
        void defineColor();
        void defineSurrounding();
        void drawSurrounding();
};







#endif // AUTOMATE_H
