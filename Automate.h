#ifndef AUTOMATE_H
#define AUTOMATE_H

#include <QApplication>
#include <QtWidgets>
#include <QPushButton>
#include <QDialog>
#include <QSpinBox>
#include <QRadioButton>
#include "Grid.h"
#include "Model.h"
#include "Library.h"
#include "Rules.h"

class Grid; //forward declaration
class Rules;

class Automate : public QWidget
{
    public:
    Automate();
        //virtual Automate* parent() {return this;}
        Library* getLib() const {return lib;}
        void setAuthozied(bool value) {authorized =value;}

    private:
        QPushButton *b_library;
        QPushButton *b_voisinage;
        QPushButton *b_rules;
        QPushButton *b_next;
        QSpinBox *b_run;
        Grid* grille;
        Library* lib;
        bool authorized;
        //Rules* rule;
        void drawInterface();

    //Boite de Dialogue
        QDialog* infos;
        QLineEdit *nom;
        QSpinBox *nb;
        QSpinBox *nb1;
        int added;
        int added_rules;
        int added_states;
        QPushButton *color;
        QColor* couleur;
        QLineEdit *label;
        QComboBox *list;
        QRadioButton *r_intension;
        QRadioButton *r_extension;


    private slots :
        void defineModel();
        void defineStates();
        void defineColor();
        void defineSurrounding();
        void drawSurrounding();
        void displaySurrounding();
        void chooseModel();
        void applyModel();
        ///void liberateDialog();
        void chooseRules();
        void defineRules();
        void defineRulesStates();
        void next();
        void run();
};







#endif // AUTOMATE_H
