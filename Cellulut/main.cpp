#include "main.h"
#include "ui/UIEngine.h"
#include "models/Library.h"
#include "models/Automate.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    UIEngine *uiEngine = new UIEngine(&app);
    uiEngine->start();

    return app.exec();
}
