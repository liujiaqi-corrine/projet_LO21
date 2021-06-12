#include "main.h"
#include "ui/UIEngine.h"
#include "models/Library.h"
#include "models/Automate.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Automate::getAutomate()->setModel(Library::getLibrary()->getListModels()->at(0));

    UIEngine *uiEngine = new UIEngine(&app);
    uiEngine->startEngine();

    return app.exec();
}
