#include "SimulationViewV2.h"

SimulationViewV2::SimulationViewV2(QWidget *parent) : QWidget(parent), board(new SimulationBoard)
{
    levelLcd = new QLCDNumber(2);
    levelLcd->setSegmentStyle(QLCDNumber::Filled);

    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);

    sliderSize = new QSlider();
    sliderSize->setMinimum(MIN_GRID_SIZE);
    sliderSize->setMaximum(MAX_GRID_SIZE);
    sliderSize->setOrientation(Qt::Orientation::Horizontal);

    inputSize = new QLineEdit();
    inputSize->setFixedWidth(30);
    inputSize->setText(QString::number(sliderSize->value()));

    QHBoxLayout *sizeLayout = new QHBoxLayout;
    sizeLayout->addWidget(new QLabel(tr("Size :")));
    sizeLayout->addWidget(inputSize);
    sizeLayout->addWidget(sliderSize);

    QWidget *sizeSelector = new QWidget();
    sizeSelector->setLayout(sizeLayout);
    sizeSelector->setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
    sizeSelector->setFixedHeight(50);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(createLabel(tr("SIMULATION")), 0, 0);
    layout->addWidget(sizeSelector, 1, 0);
    layout->addWidget(startButton, 2, 0);
    layout->addWidget(board, 0, 1, 6, 2);
    setLayout(layout);

    setWindowTitle(tr("Tetrix"));
    resize(550, 370);

    initEvents();

    qInfo() << "SimulationView::SimulationViewV2 - constructor";
}

void SimulationViewV2::initEvents(){
    connect(sliderSize, &QSlider::valueChanged, this , &SimulationViewV2::updateInputSizeValueFromInt );
    connect(inputSize, &QLineEdit::textEdited, this , &SimulationViewV2::updateInputSizeValueFromString );

    qInfo() << "SimulationViewV2::initEvents - events binded";
}

QLabel *SimulationViewV2::createLabel(const QString &text)
{
    QLabel *label = new QLabel(text);
    label->setAlignment(Qt::AlignHCenter | Qt::AlignCenter);
    return label;
}

void SimulationViewV2::updateInputSizeValueFromInt(int newValue){
    if(newValue<MIN_GRID_SIZE || newValue>MAX_GRID_SIZE) return;
    this->board->changeGridSize(newValue);
    this->inputSize->setText(QString::number(newValue));
}

void SimulationViewV2::updateInputSizeValueFromString(QString newValueAsStr){
    if(newValueAsStr == ""){
        return;
    }
    for(char const &c: newValueAsStr.toStdString()){
        if(isdigit(c)==0) return;
    }
    int newValue = newValueAsStr.toInt();
    if(newValue<MIN_GRID_SIZE || newValue>MAX_GRID_SIZE) return;
    this->board->changeGridSize(newValue);
    this->sliderSize->setValue(newValue);
}
