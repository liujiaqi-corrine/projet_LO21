#include "MainMenuView.h"

MainMenuView::MainMenuView(QWidget *_parent, UIEngine *_uiEngine) : QWidget(_parent), uiEngine(_uiEngine)
{
    this->welcomeMessageLabel = UIUtils::createLabel(tr("Bienvenue sur l'application Cellulut"), 25, true, false);
    this->editLibraryButton = new QPushButton("Gérer la bibliothèque");
    this->editLibraryButton->setFixedHeight(150);
    this->editLibraryButton->setFont(UIUtils::getFont(15,true,false,QFont::Capitalization::AllUppercase));
    this->editLibraryButton->setStyleSheet("background-color : crimson; color: white;");

    this->createModelButton = new QPushButton("Créer un modèle");
    this->createModelButton->setFixedHeight(150);
    this->createModelButton->setFont(UIUtils::getFont(15,true,false,QFont::Capitalization::AllUppercase));
    this->createModelButton->setStyleSheet("background-color : crimson; color: white;");

    this->gridLayout = new QGridLayout();
    this->gridLayout->addWidget(this->welcomeMessageLabel,0,0,1,2);
    this->gridLayout->addWidget(this->editLibraryButton, 1,0,1,1);
    this->gridLayout->addWidget(this->createModelButton,1,1,1,1);
    this->setLayout(gridLayout);

    connect(this->editLibraryButton, &QPushButton::clicked, this, &MainMenuView::editLibrary);

    qInfo() << "MainMenuView::MainMenuView - constructor";
}

MainMenuView::~MainMenuView(){
    delete this->editLibraryButton;
    delete this->createModelButton;
    delete this->welcomeMessageLabel;
    delete this->gridLayout;

    qInfo() << "MainMenuView::~MainMenuView - destructor";
}

void MainMenuView::editLibrary()
{
    QPushButton *addModelButton = new QPushButton("Ajouter\nun modèle");
    QPushButton *delModelButton = new QPushButton("Supprimer\nun modèle");
    QPushButton *addSurroundingButton = new QPushButton("Ajouter\nun voisinage");
    QPushButton *delSurroundingButton = new QPushButton("Supprimer\nun voisinage");

    addModelButton->setFixedHeight(80);
    delModelButton->setFixedHeight(80);
    addSurroundingButton->setFixedHeight(80);
    delSurroundingButton->setFixedHeight(80);

    addModelButton->setFont(UIUtils::getFont(9,false,false,QFont::Capitalization::AllUppercase));
    delModelButton->setFont(UIUtils::getFont(9,false,false,QFont::Capitalization::AllUppercase));
    addSurroundingButton->setFont(UIUtils::getFont(9,false,false,QFont::Capitalization::AllUppercase));
    delSurroundingButton->setFont(UIUtils::getFont(9,false,false,QFont::Capitalization::AllUppercase));

    QGridLayout* editLibraryLayout = new QGridLayout();
    editLibraryLayout->addWidget(addModelButton, 0, 0);
    editLibraryLayout->addWidget(delModelButton, 1, 0);
    editLibraryLayout->addWidget(addSurroundingButton, 0, 1);
    editLibraryLayout->addWidget(delSurroundingButton, 1, 1);

    this->editLibraryMenu = new QDialog(this);
    this->editLibraryMenu->setWindowTitle("Bibliothèque");
    this->editLibraryMenu->setModal(true);
    this->editLibraryMenu->setFixedSize(250,210);
    this->editLibraryMenu->setLayout(editLibraryLayout);
    this->editLibraryMenu->show();

    connect(addModelButton, &QPushButton::clicked, this, &MainMenuView::addModel);
    connect(addModelButton,&QPushButton::clicked,this->editLibraryMenu,&QDialog::close);
    connect(delModelButton, &QPushButton::clicked, this, &MainMenuView::delModel);
    connect(addSurroundingButton, &QPushButton::clicked, this, &MainMenuView::addSurrounding);
    connect(delSurroundingButton, &QPushButton::clicked, this, &MainMenuView::delSurrounding);
    return;
}

void MainMenuView::addModel()
{
    QLabel* choiceLabel = new QLabel;
    choiceLabel = UIUtils::createLabel(tr("Modèle :"), 20, false, false);

    QGridLayout* addModelLayout = new QGridLayout();
    addModelLayout->addWidget(choiceLabel, 0, 0);

    this->addModelMenu = new QDialog(this);
    this->addModelMenu->setWindowTitle("Nouveau modèle");
    this->addModelMenu->setModal(true);
    this->addModelMenu->setLayout(addModelLayout);
    this->addModelMenu->show();
}

void MainMenuView::delModel()
{
    this->delModelMenu = new QDialog(this);
    this->delModelMenu->setWindowTitle("Suppression d'un modèle");
    this->delModelMenu->setModal(true);
    //delModelMenu->setLayout(delModelLayout);
    this->delModelMenu->show();
}

void MainMenuView::addSurrounding()
{
    this->addSurroundingMenu = new QDialog(this);
    this->addSurroundingMenu->setWindowTitle("Ajout d'un voisinage");
    this->addSurroundingMenu->setModal(true);
    //addSurroundingMenu->setLayout(addSurroundingLayout);
    this->addSurroundingMenu->show();
}

void MainMenuView::delSurrounding()
{
    this->delSurroundingMenu = new QDialog(this);
    this->delSurroundingMenu->setWindowTitle("Suppression d'un voisinage");
    this->delSurroundingMenu->setModal(true);
    //delSurroundingMenu->setLayout(delSurroundingLayout);
    this->delSurroundingMenu->show();
}

