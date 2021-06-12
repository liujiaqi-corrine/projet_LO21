#ifndef LOADMODELFORMVIEW_H
#define LOADMODELFORMVIEW_H

#include "main.h"
#include "ui/UIEngine.h"
#include "models/Library.h"
#include "models/Automate.h"

class LoadModelFormView : public QWidget
{
    Q_OBJECT
    public:
        LoadModelFormView(QWidget *parent = 0, UIEngine *_uiEngine = 0);
        ~LoadModelFormView();

    private:
        UIEngine *uiEngine;
        QGridLayout *gridLayout;
        QLabel *instructionMessageLabel;
        QLabel *modelComboLabel;
        QComboBox *modelCombo;
        QStringListModel *modelComboModel;
        QPushButton *nextButton;
        QPushButton *backButton;

        void onNextButtonClick();
};

#endif // LOADMODELFORMVIEW_H
