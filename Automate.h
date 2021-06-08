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
        QPushButton *b_voisinage;
        QPushButton *b_rules;
        QPushButton *b_next;
        QPushButton *b_reset;
        QPushButton *b_config;
        QPushButton *b_random;
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
        int added_rules;
        int added_states;
        QPushButton *color;
        QColor* couleur;
        QLineEdit *label;
        QComboBox *list;
        QRadioButton *r_intension;
        QRadioButton *r_extension;
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
        ///void liberateDialog();
        void chooseRules();
        void defineRules();
        void defineRulesStates();
        void nextIntension();
        void run();
        void reset();
        void nextConfig();
        void addConfig();
        void defineConfig();
<<<<<<< HEAD
        void generateRandomGrid();
=======
        void drawConfig();
        void validateSurrounding();
        void validateConfig();
        void cellToStateMethod(int row, int column);
>>>>>>> extension
        //void setEntourage(int row, int column);

    signals:
        void cellToState(int row, int columnn, int index);
};







#endif // AUTOMATE_H
