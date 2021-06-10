#include "main.h"

#include <QApplication>
#include "data/DataEngine.h"
#include "ui/UIEngine.h"
#include "models/Library.h"
#include "models/Automate.h"
#include "models/Rule.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    DataEngine *dataEngine = new DataEngine();
    UIEngine *uiEngine = new UIEngine(&app);

    uiEngine->setInsideDataForUI(dataEngine->getInsideDataForUI());
    dataEngine->setInsideUIForData(uiEngine->getInsideUIForData());

    uiEngine->start();
    uiEngine->changeToSimulationView();

    return app.exec();
}
