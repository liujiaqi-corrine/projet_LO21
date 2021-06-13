#include "MainMenuView.h"

MainMenuView::MainMenuView(QWidget *_parent, UIEngine *_uiEngine) : QWidget(_parent), uiEngine(_uiEngine)
{
    this->welcomeMessageLabel = UIUtils::createLabel(tr("Welcome to the Cellulut application"), 25, true, false);
    this->editLibraryButton = new QPushButton("Manage the Library");
    this->editLibraryButton->setFixedHeight(150);
    this->editLibraryButton->setFont(UIUtils::getFont(15,true,false,QFont::Capitalization::AllUppercase));
    this->editLibraryButton->setStyleSheet("background-color : crimson; color: white;");

    this->createModelButton = new QPushButton("Create a Model");
    this->createModelButton->setFixedHeight(150);
    this->createModelButton->setFont(UIUtils::getFont(15,true,false,QFont::Capitalization::AllUppercase));
    this->createModelButton->setStyleSheet("background-color : crimson; color: white;");

    this->gridLayout = new QGridLayout();
    this->gridLayout->addWidget(this->welcomeMessageLabel,0,0,1,2);
    this->gridLayout->addWidget(this->editLibraryButton, 1,0,1,1);
    this->gridLayout->addWidget(this->createModelButton,1,1,1,1);
    this->setLayout(gridLayout);

    //connect(this->editLibraryButton, &QPushButton::clicked, this, &MainMenuView::editLibrary);
    connect(this->editLibraryButton, &QPushButton::clicked, this->uiEngine, &UIEngine::changeToLibraryView);
    connect(this->createModelButton, &QPushButton::clicked, this, &MainMenuView::addModel);

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
    QPushButton *addModelButton = new QPushButton("Add\n model");
    QPushButton *delModelButton = new QPushButton("Delete\n model");
    QPushButton *addSurroundingButton = new QPushButton("Add\n surrounding");
    QPushButton *delSurroundingButton = new QPushButton("Delete\n surrounding");

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
    editLibraryLayout->addWidget(addSurroundingButton, 0, 1);
    editLibraryLayout->addWidget(delModelButton, 1, 0);
    editLibraryLayout->addWidget(delSurroundingButton, 1, 1);

    this->editLibraryMenu = new QDialog(this);
    this->editLibraryMenu->setWindowTitle("Library");
    this->editLibraryMenu->setModal(true);
    this->editLibraryMenu->setFixedSize(250,210);
    this->editLibraryMenu->setLayout(editLibraryLayout);
    this->editLibraryMenu->show();

    connect(addModelButton, &QPushButton::clicked, this, &MainMenuView::addModel);
    connect(addModelButton,&QPushButton::clicked,this->editLibraryMenu,&QDialog::close);
    connect(delModelButton, &QPushButton::clicked, this, &MainMenuView::delModel);
    connect(addSurroundingButton, &QPushButton::clicked, this->uiEngine, &UIEngine::changeToCreateSurroundingFormView);
    return;
}

void MainMenuView::addModel()
{
    this-> states_added = 0;

    this->model_name = new QLineEdit;
    this->nb_states = new QSpinBox;
    this->nb_states->setMinimum(2);
    this->nb_states->setMaximum(8);

    QPushButton *cancel = new QPushButton("Return");
    QPushButton *next = new QPushButton("Next");

    QHBoxLayout *controlButtons = new QHBoxLayout;
    controlButtons->addWidget(cancel);
    controlButtons->addWidget(next);

    QFormLayout *form = new QFormLayout;
    form->addRow("Model name :", model_name);
    form->addRow("Number of states :", nb_states);

    QVBoxLayout *addModelLayout = new QVBoxLayout;
    addModelLayout->addLayout(form);
    addModelLayout->addLayout(controlButtons);

    this->addModelMenu = new QDialog(this);
    this->addModelMenu->setWindowTitle("New model");
    this->addModelMenu->setModal(true);
    this->addModelMenu->setLayout(addModelLayout);
    this->addModelMenu->show();

    QObject::connect(next,&QPushButton::clicked,this,&MainMenuView::addState);
    QObject::connect(next,&QPushButton::clicked,this->addModelMenu,&QDialog::close);
    QObject::connect(cancel,&QPushButton::clicked,this->addModelMenu,&QDialog::close);
}

void MainMenuView::addState()
{
    if (!this->states_added)
        Library::getLibrary()->create_Model(this->model_name->text().toStdString()); // Adding model to library

    else if(this->states_added > 0)
        Library::getLibrary()->getListModels()->at(Library::getLibrary()->getListModels()->size()-1)->add_State(new State(states_added-1, this->state_label->text().toStdString(), this->colorsCombo->currentText().toStdString())); // State dead added

    if (this->states_added == this->nb_states->value())
        return;

    QPushButton *next = new QPushButton("Next");

    QHBoxLayout *controlButtons = new QHBoxLayout;
    controlButtons->addWidget(next);

    this->states_added += 1;
    this->state_label = new QLineEdit;

    this->colorsCombo = new QComboBox();
    this->colorsCombo->addItem("white");
    this->colorsCombo->addItem("red");
    this->colorsCombo->addItem("orange");
    this->colorsCombo->addItem("yellow");
    this->colorsCombo->addItem("green");
    this->colorsCombo->addItem("blue");
    this->colorsCombo->addItem("violet");
    this->colorsCombo->addItem("black");

    QFormLayout *form = new QFormLayout;
    form->addRow("Label:", state_label);
    form->addRow("Couleur:", colorsCombo);

    QVBoxLayout *addStateLayout = new QVBoxLayout;
    addStateLayout->addLayout(form);
    addStateLayout->addLayout(controlButtons);

    this->addStateMenu = new QDialog(this);
    this->addStateMenu->setWindowTitle("New state");
    this->addStateMenu->setModal(true);
    this->addStateMenu->setLayout(addStateLayout);
    this->addStateMenu->show();


    QObject::connect(next,&QPushButton::clicked,this,&MainMenuView::addState);
    if (this->states_added == this->nb_states->value())
        QObject::connect(next,&QPushButton::clicked,this,&MainMenuView::setSurrounding);
    QObject::connect(next,&QPushButton::clicked,this->addStateMenu,&QDialog::close);
}

void MainMenuView::setSurrounding()
{
    QStringList surroundingComboStringList;
    vector<Surrounding*> *listOfSurroundings = Library::getLibrary()->getListSurroundings();
    for(unsigned int i = 0; i < listOfSurroundings->size(); i++){
        surroundingComboStringList << listOfSurroundings->at(i)->getNameAsQString();
    }

    QPushButton *confirm = new QPushButton("Confirm");

    QHBoxLayout *controlButtons = new QHBoxLayout;
    controlButtons->addWidget(confirm);

    this->surroundingComboModel = new QStringListModel();
    this->surroundingComboModel->setStringList(surroundingComboStringList);

    this->surroundingCombo = new QComboBox();
    this->surroundingCombo->setModel(surroundingComboModel);

    QFormLayout *form = new QFormLayout;
    form->addRow("Chose surrounding :", surroundingCombo);

    QVBoxLayout *setSurroundingLayout = new QVBoxLayout;
    setSurroundingLayout->addLayout(form);
    setSurroundingLayout->addLayout(controlButtons);

    this->setSurroundingMenu = new QDialog(this);
    this->setSurroundingMenu->setWindowTitle("Surrounding choice");
    this->setSurroundingMenu->setModal(true);
    this->setSurroundingMenu->setLayout(setSurroundingLayout);
    this->setSurroundingMenu->show();

    QObject::connect(confirm,&QPushButton::clicked,this->setSurroundingMenu,&QDialog::close);
    QObject::connect(confirm,&QPushButton::clicked,this,&MainMenuView::onClickSubmitSetSurrounding);
    QObject::connect(confirm,&QPushButton::clicked,this,&MainMenuView::addRule);
}

void MainMenuView::onClickSubmitSetSurrounding()
{
    int selectedSurrounding = this->surroundingCombo->currentIndex();
    Library::getLibrary()->get_Model(Library::getLibrary()->getListModels()->size()-1)->setSurrounding(Library::getLibrary()->getListSurroundings()->at(selectedSurrounding));
    qInfo() << "Surrounding set on "<< Library::getLibrary()->getListSurroundings()->at(selectedSurrounding)->getNameAsQString();
}

void MainMenuView::addRule()
{
    QPushButton *cancel = new QPushButton("Return");
    QPushButton *add_rule = new QPushButton("Add rule");

    QHBoxLayout *controlButtons = new QHBoxLayout;
    controlButtons->addWidget(cancel);
    controlButtons->addWidget(add_rule);

    QStringList stateComboStringList;
    vector<State*> *listOfStates = Library::getLibrary()->get_Model(Library::getLibrary()->getListModels()->size()-1)->getListStates();
    for(unsigned int i = 0; i < listOfStates->size(); i++){
        stateComboStringList << listOfStates->at(i)->getLabelAsQString();
    }

    this->currentStateComboModel = new QStringListModel();
    this->currentStateComboModel->setStringList(stateComboStringList);

    this->currentStateCombo = new QComboBox();
    this->currentStateCombo->setModel(currentStateComboModel);

    this->nb_states_nearby = new QSpinBox;
    this->nb_states_nearby->setMinimum(0);
    this->nb_states_nearby->setMaximum(8);

    this->stateNearbyComboModel = new QStringListModel();
    this->stateNearbyComboModel->setStringList(stateComboStringList);

    this->stateNearbyCombo = new QComboBox();
    this->stateNearbyCombo->setModel(stateNearbyComboModel);

    this->nextStateComboModel = new QStringListModel();
    this->nextStateComboModel->setStringList(stateComboStringList);

    this->nextStateCombo = new QComboBox();
    this->nextStateCombo->setModel(nextStateComboModel);

    QFormLayout *form = new QFormLayout;
    form->addRow("Si la cellule est dans l'état:", currentStateCombo);
    form->addRow("Qu'elle a :", nb_states_nearby);
    form->addRow("Voisins dans l'état :", stateNearbyCombo);
    form->addRow("Alors elle devient :", nextStateCombo);

    QVBoxLayout *addRuleLayout = new QVBoxLayout;
    addRuleLayout->addLayout(form);
    addRuleLayout->addLayout(controlButtons);


    this->addRuleMenu = new QDialog(this);
    this->addRuleMenu->setWindowTitle("New rule");
    this->addRuleMenu->setModal(true);
    this->addRuleMenu->setLayout(addRuleLayout);
    this->addRuleMenu->show();

    QObject::connect(add_rule,&QPushButton::clicked,this,&MainMenuView::onClickSubmitAddRule);
    QObject::connect(add_rule,&QPushButton::clicked,this,&MainMenuView::addRule);
    QObject::connect(add_rule,&QPushButton::clicked,this->addRuleMenu,&QDialog::close);
    QObject::connect(cancel,&QPushButton::clicked,this->addRuleMenu,&QDialog::close);
}

void MainMenuView::onClickSubmitAddRule()
{
    int A = this->currentStateCombo->currentIndex();
    int B = this->nb_states_nearby->value();
    int C = this->stateNearbyCombo->currentIndex();
    int D = this->nextStateCombo->currentIndex();
    qInfo() << A << this->currentStateCombo->currentIndex();
    Rule_int* new_rule = new Rule_int(A, B, C, D);
    Library::getLibrary()->get_Model(Library::getLibrary()->getListModels()->size()-1)->add_Rule_int(new_rule);
}

void MainMenuView::delModel()
{

    QStringList modelComboStringList;
    vector<Model*> *listOfModels = Library::getLibrary()->getListModels();
    for(unsigned int i = 3; i < listOfModels->size(); i++){
        modelComboStringList << listOfModels->at(i)->getTitleAsQString();
    }

    QPushButton *cancel = new QPushButton("Return");
    QPushButton *confirm = new QPushButton("Confirm");

    this->modelComboModel = new QStringListModel();
    this->modelComboModel->setStringList(modelComboStringList);

    this->modelCombo = new QComboBox();
    this->modelCombo->setModel(modelComboModel);
    this->modelCombo->setToolTip("Impossible de supprimer les modèles pré-existants");

    QFormLayout *form = new QFormLayout;
    form->addRow("Delete model :", modelCombo);

    QHBoxLayout *controlButtons = new QHBoxLayout;
    controlButtons->addWidget(cancel);
    controlButtons->addWidget(confirm);

    QVBoxLayout *delModelLayout = new QVBoxLayout;
    delModelLayout->addLayout(form);
    delModelLayout->addLayout(controlButtons);

    this->delModelMenu = new QDialog(this);
    this->delModelMenu->setWindowTitle("Deleting model");
    this->delModelMenu->setModal(true);
    delModelMenu->setLayout(delModelLayout);
    this->delModelMenu->show();

    QObject::connect(cancel,&QPushButton::clicked,this->delModelMenu,&QDialog::close);
    QObject::connect(confirm,&QPushButton::clicked,this->delModelMenu,&QDialog::close);
    QObject::connect(confirm,&QPushButton::clicked,this,&MainMenuView::onClickSubmitDelModel);
}

void MainMenuView::onClickSubmitDelModel()
{
    int selectedModel = this->modelCombo->currentIndex();
    Library::getLibrary()->del_Model(Library::getLibrary()->getListModels()->at(selectedModel)->getId_Model());
}


