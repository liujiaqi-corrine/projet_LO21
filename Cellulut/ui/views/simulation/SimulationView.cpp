#include "SimulationView.h"

SimulationView::SimulationView(QWidget *parent, UIEngine *_uiEngine) : QWidget(parent), uiEngine(_uiEngine)
{
    Automate::getAutomate()->getHistoric()->clear();
    modelForSimulation = Automate::getAutomate()->getModel();
    Grid::getGrid()->removeAllCells();
    Automate::getAutomate()->init_Grid(MIN_GRID_SIZE);

    this->board = new SimulationBoard(0);

    this->sliderSize = new QSlider();
    this->sliderSize->setMinimum(MIN_GRID_SIZE);
    this->sliderSize->setMaximum(MAX_GRID_SIZE);
    this->sliderSize->setOrientation(Qt::Orientation::Horizontal);
    this->sliderSize->setSizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

    this->inputSize = new QLineEdit();
    this->inputSize->setFixedWidth(30);
    this->inputSize->setText(QString::number(sliderSize->value()));

    QHBoxLayout *sizeLayout = new QHBoxLayout;
    sizeLayout->addWidget(new QLabel(tr("Size :")));
    sizeLayout->addWidget(inputSize);

    this->sizeDisplay = new QWidget();
    sizeDisplay->setLayout(sizeLayout);
    sizeDisplay->setSizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
    sizeDisplay->setFixedHeight(50);
    sizeDisplay->setFixedWidth(200);

    this->statesDisplay = new StatesDisplay(0);

    this->simulationButtonsBar = new SimulationButtonsBar(0);

    this->gridLayout = new QGridLayout;
    setLayout(this->gridLayout);
    setStyleSheet(tr(this->styleSheet));

    // Random configuration button
    this->randomInitializationButton = new QPushButton("Initialisation aléatoire");
    this->randomInitializationButton->setFont(UIUtils::getFont(12,false,false));

    // Automatic simulation
    this->simulationThread = new SimulationThread(this);

    // Simulation Speed
    this->simulationSpeed = new QWidget;
    this->simulationSpeedFactorLabel = new QLabel("x1");
    this->increaseSimulationSpeed = new QPushButton;
    this->increaseSimulationSpeed->setIcon(QIcon(":/icons/forward.svg"));
    this->increaseSimulationSpeed->setDisabled(true);
    this->increaseSimulationSpeed->setToolTip("Accélérer la simulation");
    this->decreaseSimulationSpeed = new QPushButton;
    this->decreaseSimulationSpeed->setIcon(QIcon(":/icons/backward.svg"));
    this->decreaseSimulationSpeed->setDisabled(true);
    this->decreaseSimulationSpeed->setToolTip("Ralentir la simulation");
    QHBoxLayout *simulationSpeedLayout = new QHBoxLayout;
    simulationSpeedLayout->addWidget(simulationSpeedFactorLabel);
    simulationSpeedLayout->addWidget(decreaseSimulationSpeed);
    simulationSpeedLayout->addWidget(increaseSimulationSpeed);
    this->simulationSpeed->setLayout(simulationSpeedLayout);

    setupLabelsForModel();
    setupGridLayout();
    initEvents();

    qInfo() << "SimulationView::SimulationView - constructor";
}

SimulationView::~SimulationView(){
    delete board;
    delete inputSize;
    delete sliderSize;
    delete randomInitializationButton;

    qInfo() << "SimulationView::SimulationView - destructor";
}

void SimulationView::initEvents(){
    connect(sliderSize, &QSlider::valueChanged, this , &SimulationView::updateInputSizeValueFromInt );
    connect(inputSize, &QLineEdit::textEdited, this , &SimulationView::updateInputSizeValueFromString );
    connect(board, &SimulationBoard::initialConfigurationChanged, statesDisplay, &StatesDisplay::refreshCounters);
    connect(simulationButtonsBar, &SimulationButtonsBar::stepForward, this, &SimulationView::generateNextStep);
    connect(simulationButtonsBar, &SimulationButtonsBar::stepBackward, this, &SimulationView::generateBackStep);
    connect(randomInitializationButton, &QPushButton::clicked, this, &SimulationView::onClickRandomInitialization);
    connect(simulationButtonsBar, &SimulationButtonsBar::start, this, &SimulationView::onClickStart);
    connect(simulationButtonsBar, &SimulationButtonsBar::stop, this, &SimulationView::onClickStop);
    connect(simulationThread, &SimulationThread::nextStepCalculated, this, &SimulationView::generateNextStep);
    connect(increaseSimulationSpeed, &QPushButton::clicked, this, &SimulationView::onClickIncreaseSpeed);
    connect(decreaseSimulationSpeed, &QPushButton::clicked, this, &SimulationView::onClickDecreaseSpeed);
    qInfo() << "SimulationView::initEvents - events binded";
}

void SimulationView::updateInputSizeValueFromInt(int newValue){
    Automate::getAutomate()->getHistoric()->clear();
    this->changeGridSize(newValue);
}

void SimulationView::updateInputSizeValueFromString(QString newValueAsStr){
    Automate::getAutomate()->getHistoric()->clear();
    if(newValueAsStr == ""){
        return;
    }
    for(char const &c: newValueAsStr.toStdString()){
        if(isdigit(c)==0) return;
    }
    int newValue = newValueAsStr.toInt();
    this->changeGridSize(newValue);
}

void SimulationView::changeGridSize(int newValue){
    if(newValue<MIN_GRID_SIZE || newValue>MAX_GRID_SIZE) return;
    Grid::getGrid()->removeAllCells();
    Automate::getAutomate()->init_Grid(newValue);
    this->board->refreshGrid();
    this->inputSize->setText(QString::number(newValue));
}

void SimulationView::setupGridLayout(){
    this->gridLayout->addWidget(UIUtils::createLabel("Configurer la simulation\nen cliquant sur la grille", 15, true, false), 0, 2,1,4);
    this->gridLayout->addWidget(this->modelTitle, 1, 0,1,2);
    this->gridLayout->addWidget(this->modelDescription, 2, 0,1,2);
    this->gridLayout->addWidget(this->modelAuthor, 3, 0);
    this->gridLayout->addWidget(this->modelDate, 3, 1);
    this->gridLayout->addWidget(this->sizeDisplay, 5, 0, 1,2);
    this->gridLayout->addWidget(this->sliderSize, 6, 0, 1,2);
    this->gridLayout->addWidget(this->randomInitializationButton, 7, 0, 1, 2);
    this->gridLayout->addWidget(this->board, 1, 2, 7, 4);
    this->gridLayout->addWidget(createLabel("Etats :", "states", 12, false, false), 1, 6,1,2);
    this->gridLayout->addWidget(this->statesDisplay, 2,6,6,2);
    this->gridLayout->addWidget(this->simulationButtonsBar, 7,2,1,4);
    this->gridLayout->addWidget(this->simulationSpeed, 7,6,1,2);
}

void SimulationView::setupLabelsForModel(){
    this->modelTitle = createLabel(this->modelForSimulation->getTitleAsQString(), "modelTitle", 14, true, true);
    this->modelDescription = createLabel(this->modelForSimulation->getDescriptionAsQString(), "modelDescription", 10, false, true);
    this->modelAuthor = createLabel(this->modelForSimulation->getAuthorAsQString(), "modelAuthor", 10, false, false);
    this->modelDate = createLabel(this->modelForSimulation->getDateAsQString(), "modelDate", 10, false, false);
}

QLabel *SimulationView::createLabel(const QString &text, const QString &objectName, int fontSize, bool isBold, bool isItalic){
    QLabel *label = new QLabel(text);
    label->setObjectName(objectName);
    label->setAlignment(Qt::AlignHCenter|Qt::AlignCenter);

    QFont labelFont;
    labelFont.setBold(isBold);
    labelFont.setItalic(isItalic);
    labelFont.setPointSize(fontSize);
    labelFont.setFamily("Bahnschrift");
    label->setFont(labelFont);

    return label;
}

void SimulationView::generateNextStep(){
    if (!Automate::getAutomate()->getHistoric()->size())
        Automate::getAutomate()->save_current_config();
    Automate::getAutomate()->next_generation();
    if(Automate::getAutomate()->check_stability())
        qInfo() << "Stable configuration";
    this->board->refreshGrid();
}

void SimulationView::generateBackStep(){
    if(!Automate::getAutomate()->back_generation())
        qInfo() << "No backtracking possible";
    this->board->refreshGrid();
}

void SimulationView::onClickRandomInitialization(){
    Automate::getAutomate()->random_init();
    this->board->refreshGrid();
}

void SimulationView::onClickStart(){
    this->simulationThread->Stop = false;
    if (this->speedFactor == 1)
        this->decreaseSimulationSpeed->setDisabled(true);
    else
        this->decreaseSimulationSpeed->setDisabled(false);
    if (this->speedFactor == MAX_SIMULATION_SPEED)
        this->increaseSimulationSpeed->setDisabled(true);
    else
        this->increaseSimulationSpeed->setDisabled(false);
    this->simulationButtonsBar->setStartButtonDisabled(true);
    this->simulationButtonsBar->setStopButtonDisabled(false);
    this->simulationButtonsBar->setStepBackwardButtonDisabled(true);
    this->simulationButtonsBar->setStepForwardButtonDisabled(true);
    this->inputSize->setDisabled(true);
    this->sliderSize->setDisabled(true);
    this->randomInitializationButton->setDisabled(true);
    this->simulationThread->start();
}

void SimulationView::onClickStop(){
    this->simulationThread->Stop = true;
    if (this->speedFactor == 1)
        this->decreaseSimulationSpeed->setDisabled(true);
    else
        this->decreaseSimulationSpeed->setDisabled(false);
    if (this->speedFactor == MAX_SIMULATION_SPEED)
        this->increaseSimulationSpeed->setDisabled(true);
    else
        this->increaseSimulationSpeed->setDisabled(false);
    this->simulationButtonsBar->setStartButtonDisabled(false);
    this->simulationButtonsBar->setStopButtonDisabled(true);
    this->simulationButtonsBar->setStepBackwardButtonDisabled(false);
    this->simulationButtonsBar->setStepForwardButtonDisabled(false);
    this->inputSize->setDisabled(false);
    this->sliderSize->setDisabled(false);
    this->randomInitializationButton->setDisabled(false);
}

void SimulationView::onClickIncreaseSpeed(){
    this->speedFactor=this->speedFactor+1;
    if(this->speedFactor<=MAX_SIMULATION_SPEED){
        string speedFactorLabel = "x"+std::to_string(this->speedFactor);
        this->simulationSpeedFactorLabel->setText(QString::fromStdString(speedFactorLabel));
        this->simulationThread->setSleepDuration(MIN_SIMULATION_TICK/this->speedFactor);
        if(this->speedFactor==MAX_SIMULATION_SPEED){
            this->increaseSimulationSpeed->setDisabled(true);
        }
    }

    if(this->speedFactor>1){
        this->decreaseSimulationSpeed->setDisabled(false);
    }

}

void SimulationView::onClickDecreaseSpeed(){
    this->speedFactor=this->speedFactor-1;
    if(this->speedFactor>=1){
        string speedFactorLabel = "x"+std::to_string(this->speedFactor);
        this->simulationSpeedFactorLabel->setText(QString::fromStdString(speedFactorLabel));
        this->simulationThread->setSleepDuration(MIN_SIMULATION_TICK/this->speedFactor);
        if(this->speedFactor==1){
            this->decreaseSimulationSpeed->setDisabled(true);
        }
    }
    if(this->speedFactor<MAX_SIMULATION_SPEED){
        this->increaseSimulationSpeed->setDisabled(false);
    }
}
