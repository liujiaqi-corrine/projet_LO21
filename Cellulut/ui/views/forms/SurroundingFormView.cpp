#include "SurroundingFormView.h"

SurroundingFormView::SurroundingFormView(QWidget *_parent, UIEngine* _uiEngine): QWidget(_parent), uiEngine(_uiEngine)
{
    this->gridLayout = new QGridLayout;
    this->instructionMessageLabel = UIUtils::createLabel("New surrounding",12,true);

    this->surroundingNameLabel = UIUtils::createLabel("Label :",12,false);
    this->surroundingNameInput = new QLineEdit;

    this->surroundingRadiusLabel = UIUtils::createLabel("Radius :", 12, false);
    this->surroundingRadiusInput = new QSpinBox;
    this->surroundingRadiusInput->setValue(1);
    this->surroundingRadiusInput->setMinimum(1);

    this->board = new SurroundingBoard(0);

    this->submitFormButton = UIUtils::createButton("Add");

    this->gridLayout->addWidget(this->instructionMessageLabel,0,0,1,2);
    this->gridLayout->addWidget(this->surroundingNameLabel, 1,0,1,1);
    this->gridLayout->addWidget(this->surroundingNameInput, 1, 1, 1, 1);
    this->gridLayout->addWidget(this->surroundingRadiusLabel, 2,0,1,1);
    this->gridLayout->addWidget(this->surroundingRadiusInput, 2,1,1,1);
    this->gridLayout->addWidget(this->board,3,0,1,2);
    this->gridLayout->addWidget(this->submitFormButton, 4, 0, 1, 2);

    this->setLayout(this->gridLayout);

    connect(this->surroundingRadiusInput, &QSpinBox::textChanged, this->board, &SurroundingBoard::changeBoardSize);
    connect(this->submitFormButton, &QPushButton::clicked, this, &SurroundingFormView::onClickSubmit);
}

SurroundingFormView::~SurroundingFormView()
{
    delete this->surroundingNameInput;
    delete this->surroundingNameLabel;
    delete this->instructionMessageLabel;
    delete this->surroundingRadiusLabel;
    delete this->surroundingRadiusInput;
    delete this->gridLayout;
}

void SurroundingFormView::onClickSubmit(){
    string surroundingName = this->surroundingNameInput->text().toStdString();
    int surroundingRadius = this->surroundingRadiusInput->value();

    Surrounding *newSurrounding = Library::getLibrary()->create_Surrounding(surroundingName);
    newSurrounding->setRadius(surroundingRadius);
    newSurrounding->setInteraction(this->board->getBoardAsVector());

    this->uiEngine->changeToLibraryView();
}
