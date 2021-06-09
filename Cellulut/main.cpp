#include "main.h"
#include <QApplication>
#include "controllers/C_MainWindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Instantiate main window controller and display view
    C_MainWindow *mainWindowController = new C_MainWindow(&app);
    mainWindowController->init();

    // Show the view
    mainWindowController->getView()->show();

    return app.exec();
}
