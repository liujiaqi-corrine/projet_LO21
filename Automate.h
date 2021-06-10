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
    //Macro obligatoire car signaux (et slots) personalisé
    Q_OBJECT

    public:
    Automate();
        //virtual Automate* parent() {return this;}
        Library* getLib() const {return lib;}

    private:
        QPushButton *b_library;
        QPushButton *b_surrounding;
        QPushButton *b_voisinage;
        QPushButton *b_rules;
        QPushButton *b_next;
        QPushButton *b_reset;
        QPushButton *b_config;
        QPushButton *b_random;
        QPushButton *b_intension;
        QSpinBox *b_run;
        QLCDNumber* b_number;
        Grid* grille;
        Library* lib;
        int ran;
        int total_ran;
        //Rules* rule;
        void drawInterface();

    //Boite de Dialogue
        QDialog* infos;
        QLineEdit *nom;
        QSpinBox *nb;
        QSpinBox *nb1;
        int added;
        QPushButton *color;
        QColor* couleur;
        QLineEdit *label;
        QComboBox* list;
        QComboBox* list1;
        QComboBox* list2;
        Grid* voisins;



    private slots :
        void defineModel();
        void defineStates();
        void defineColor();
        void defineSurrounding();
        void drawSurrounding();
        void displaySurrounding();
        void chooseModel();
        void applyModel();
        ///void liberateMemoryDialog();
        void defineRuleIntension();
        State* nextIntension(int i, int j);
        void run();
        void reset();
        State* nextConfig(int i, int j);
        void generateRandomGrid();
        void drawConfig();
        void validateSurrounding();
        void validateConfig();
        void cellToStateMethod(int row, int column);
        void chooseSurrounding();
        void applySurrounding();
        void validateRuleIntension();


    signals:
        void cellToState(int row, int columnn, int index);
};


#endif // AUTOMATE_H
