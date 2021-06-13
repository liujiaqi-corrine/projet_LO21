#ifndef MAINMENUVIEW_H
#define MAINMENUVIEW_H

#include "main.h"
#include "ui/UIEngine.h"

class UIEngine;

class MainMenuView : public QWidget
{
    Q_OBJECT
    public:
        MainMenuView(QWidget *parent = 0, UIEngine *uiEngine = 0);
        ~MainMenuView();

    signals:
        void createModelClicked();

    private:
        UIEngine *uiEngine;
        QLabel *welcomeMessageLabel;
        QPushButton *createModelButton;
        QPushButton *editLibraryButton;
        QGridLayout *gridLayout;
        QDialog* editLibraryMenu;
        QDialog* addModelMenu;
        QDialog* addStateMenu;
        QDialog* delModelMenu;
        QDialog* addSurroundingMenu;
        QDialog* delSurroundingMenu;

        QLineEdit* model_name;
        QSpinBox* nb_states;
        unsigned int states_added;

            QPushButton *color;
            QColor* couleur;
            QLineEdit *label;
            QComboBox* list;
            QComboBox* list1;
            QComboBox* list2;

    private slots:
        void editLibrary();
        void addModel();
        void addState();
        void delModel();
        void addSurrounding();
        void delSurrounding();
};

#endif // MAINMENUVIEW_H
