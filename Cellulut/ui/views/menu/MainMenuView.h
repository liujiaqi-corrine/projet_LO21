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
        QDialog* setSurroundingMenu;
        QDialog* addRuleMenu;

        QLineEdit* model_name;
        QSpinBox* nb_states;
        unsigned int states_added;

        QLineEdit* state_label;
        QComboBox* colorsCombo;

        QComboBox* modelCombo;
        QStringListModel* modelComboModel;

        QComboBox* surroundingCombo;
        QStringListModel* surroundingComboModel;

        QComboBox* currentStateCombo;
        QStringListModel* currentStateComboModel;

        QSpinBox* nb_states_nearby;

        QComboBox* stateNearbyCombo;
        QStringListModel* stateNearbyComboModel;

        QComboBox* nextStateCombo;
        QStringListModel* nextStateComboModel;

    private slots:
        void editLibrary();
        void addModel();
        void addState();
        void setSurrounding();
        void onClickSubmitSetSurrounding();
        void addRule();
        void onClickSubmitAddRule();
        void delModel();
        void onClickSubmitDelModel();
};

#endif // MAINMENUVIEW_H
