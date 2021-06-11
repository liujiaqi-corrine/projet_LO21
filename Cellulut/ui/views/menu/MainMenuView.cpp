#include "MainMenuView.h"

MainMenuView::MainMenuView(QWidget *_parent, UIEngine *_uiEngine) : QWidget(_parent), uiEngine(_uiEngine)
{
    this->welcomeMessageLabel = UIUtils::createLabel(tr("Bienvenue sur l'application Cellulut"), 16, true, false);
    this->createModelButton = new QPushButton("Créer un modèle");
    this->createModelButton->setFixedHeight(150);
    this->createModelButton->setFont(UIUtils::getFont(12,true,false,QFont::Capitalization::AllUppercase));
    this->createModelButton->setDisabled(true);
    this->loadModelButton = new QPushButton("Charger un modèle");
    this->loadModelButton->setFixedHeight(150);
    this->loadModelButton->setFont(UIUtils::getFont(12,true,false,QFont::Capitalization::AllUppercase));

    this->gridLayout = new QGridLayout();
    this->gridLayout->addWidget(this->welcomeMessageLabel,0,0,1,2);
    this->gridLayout->addWidget(this->createModelButton, 1,0,1,1);
    this->gridLayout->addWidget(this->loadModelButton,1,1,1,1);
    this->setLayout(gridLayout);

    connect(this->loadModelButton, &QPushButton::clicked, this->uiEngine, &UIEngine::changeToLoadModelFormView);

    qInfo() << "MainMenuView::MainMenuView - constructor";
}

MainMenuView::~MainMenuView(){
    delete this->loadModelButton;
    delete this->createModelButton;
    delete this->welcomeMessageLabel;
    delete this->gridLayout;

    qInfo() << "MainMenuView::~MainMenuView - destructor";
}
