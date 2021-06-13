#include "LibraryView.h"

LibraryView::LibraryView(QWidget *parent, UIEngine *_uiEngine) : QWidget(parent), uiEngine(_uiEngine)
{
    this->gridLayout = new QGridLayout;
    int row = 0;

    // WIDGET TITLE
    this->widgetTitle = UIUtils::createLabel("Library",15, true);
    this->gridLayout->addWidget(widgetTitle, row, 0, 1, 3);

    row = row+1;

    // SURROUNDINGS
    QLabel *surroundingsTitle = UIUtils::createLabel("Surroundings :",12, false,true);
    this->gridLayout->addWidget(surroundingsTitle, row, 0, 1, 3);

    row = row+1;

    vector<Surrounding*> *listOfSurroundings = Library::getLibrary()->getListSurroundings();
    for(unsigned int i = 0; i < listOfSurroundings->size(); i++){
        Surrounding *surrounding = listOfSurroundings->at(i);
        int surroundingIndex= surrounding->getId_Surrounding();
        QLineEdit *surroundingName = new QLineEdit;
        surroundingName->setText(QString::fromStdString(surrounding->getName()));
        surroundingName->setDisabled(true);

        QPushButton *viewButton = UIUtils::createButton("View/Edit",12);
        viewButton->setObjectName("viewSurroundingButton_"+QString::number(surroundingIndex));
        connect(viewButton, &QPushButton::clicked, this, &LibraryView::onViewSurroundingButtonClicked);
        QPushButton *deleteButton = UIUtils::createButton("Delete",12);
        deleteButton->setObjectName("deleteSurroundingButton_"+QString::number(surroundingIndex));
        connect(deleteButton, &QPushButton::clicked, this, &LibraryView::onDeleteSurroundingButtonClicked);

        this->gridLayout->addWidget(surroundingName, row, 0, 1, 1);
        this->gridLayout->addWidget(viewButton, row, 1, 1, 1);
        this->gridLayout->addWidget(deleteButton, row, 2, 1, 1);
        row = row+1;
    }

    QPushButton *addSurroundingButton = UIUtils::createButton("Add new surrounding", 12, false, false);
    this->gridLayout->addWidget(addSurroundingButton, row, 0, 1, 1);
    connect(addSurroundingButton, &QPushButton::clicked, this->uiEngine, &UIEngine::changeToCreateSurroundingFormView);

    row = row+1;

    // MODELS
    QLabel *modelsTitle = UIUtils::createLabel("Models :",12, false,true);
    this->gridLayout->addWidget(modelsTitle, row, 0, 1, 3);

    row = row+1;

    vector<Model*> *listOfModels = Library::getLibrary()->getListModels();
    for(unsigned int i = 0; i < listOfModels->size(); i++){
        Model *model = listOfModels->at(i);
        int modelIndex = model->getId_Model();
        QLineEdit *modelName = new QLineEdit;
        modelName->setText(QString::fromStdString(model->getTitle()));
        modelName->setDisabled(true);

        QPushButton *deleteButton = UIUtils::createButton("Delete",12);
        deleteButton->setObjectName("deleteModelButton_"+QString::number(modelIndex));
        connect(deleteButton, &QPushButton::clicked, this, &LibraryView::onDeleteModelButtonClicked);

        this->gridLayout->addWidget(modelName, row, 0, 1, 1);
        this->gridLayout->addWidget(deleteButton, row, 1, 1, 1);
        row = row+1;
    }

    this->setLayout(this->gridLayout);

    //qInfo() << "LibraryView::LibraryView - constructor";
}

LibraryView::~LibraryView()
{
    //delete this->widgetTitle;
    delete this->gridLayout;
}

void LibraryView::onViewSurroundingButtonClicked()
{
    //qInfo() << "LibraryView::onViewSurroundingButtonClicked";

    QObject* obj = sender();
    qInfo() << obj->objectName();
}


void LibraryView::onDeleteSurroundingButtonClicked()
{
    //qInfo() << "LibraryView::onDeleteSurroundingButtonClicked";

    int surroundingIndex = this->getIDFromObjectName(sender());
    Library::getLibrary()->del_Surrounding(surroundingIndex);
    this->uiEngine->changeToLibraryView();
}

void LibraryView::onDeleteModelButtonClicked()
{
    //qInfo() << "LibraryView::onDeleteModelButtonClicked";

    int modelIndex = this->getIDFromObjectName(sender());
    Library::getLibrary()->del_Model(modelIndex);
    this->uiEngine->changeToLibraryView();
}

int LibraryView::getIDFromObjectName(QObject *sender)
{
    QString objectName = sender->objectName();
    int delimiterPos = objectName.toStdString().find("_");
    string idAsString = objectName.toStdString().substr(delimiterPos+1, objectName.toStdString().size());
    return stoi(idAsString);
}
