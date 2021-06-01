#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <QApplication>
#include <QtWidgets>
#include <QPushButton>
#include <QDialog>
#include <QSpinBox>
#include "Grid.h"
#include "Model.h"
#include "Library.h"

class Grid; //forward declaration

class Automate : public QWidget
{
    public:
    Automate();
        //virtual Automate* parent() {return this;}
        Library* getLib() const {return lib;}

    private:
        QPushButton *b_library;
        QPushButton *b_voisinage;
        Grid* grille;
        //Model* model;
        Library* lib;
        void drawInterface();

    //Boite de Dialogue
        QDialog* infos;
        QLineEdit *nom;
        QSpinBox *nb;
        int added;
        QPushButton *color;
        QColor* couleur;
        QLineEdit *label;
        QComboBox *list;


    private slots :
        void defineModel();
        void defineStates();
        void defineColor();
        void defineSurrounding();
        void drawSurrounding();
        void displaySurrounding();
        void chooseModel();
        void applyModel();
        void liberateDialog();
};







#endif // AUTOMATE_H
