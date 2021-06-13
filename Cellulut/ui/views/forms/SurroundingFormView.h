#ifndef SURROUNDINGFORMVIEW_H
#define SURROUNDINGFORMVIEW_H

#include "main.h"
#include "ui/UIEngine.h"
#include "SurroundingBoard.h"

class SurroundingFormView : public QWidget
{
    Q_OBJECT
public:
    SurroundingFormView(QWidget *parent = 0, UIEngine *uiEngine = 0);
    ~SurroundingFormView();

    void onClickSubmit();
private:
    UIEngine *uiEngine;
    QGridLayout *gridLayout;
    QLabel *instructionMessageLabel;
    QLabel *surroundingNameLabel;
    QLineEdit *surroundingNameInput;
    QLabel *surroundingRadiusLabel;
    QSpinBox *surroundingRadiusInput;
    SurroundingBoard *board;
    QPushButton *submitFormButton;
};

#endif // SURROUNDINGFORMVIEW_H
