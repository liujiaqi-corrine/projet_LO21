#include "main.h"
#include <QApplication>
#include "controllers/C_MainWindow.h"
#include "models/Library.h"
#include "models/Automate.h"
#include <unistd.h>

void ajout_donnee()
{
    // Ajout du modèle Life Game
    Model* game_life_model = new Model(1,"Jeu de la vie");

    // States
    State* vivant = new State(1, "1","noir");
    game_life_model->add_State(vivant);
    game_life_model->getListStates()->at(0)->setLabel("0");

    // Surrounding
    Surrounding* game_life_surround = new Surrounding("Jeu de la vie");
    game_life_surround->addInteraction({false, true, false});
    game_life_surround->addInteraction({true, true, true});
    game_life_surround->addInteraction({false, true, false});
    game_life_model->setSurrounding(game_life_surround);


    // Rules
    Rule_int* rule1 = new Rule_int(1, 0, 0, 0); // Par défaut, une cellule devient morte
    Rule_int* rule2 = new Rule_int(0, 3, 1, 1); // Une cellule morte avec 3 voisins vivants devient vivante
    Rule_int* rule3 = new Rule_int(1, 2, 1, 1); // Une cellule vivante avec 2 voisins vivants devient vivante
    Rule_int* rule4 = new Rule_int(1, 3, 1, 1); // Une cellule vivante avec 3 voisins vivants devient vivante
    game_life_model->add_Rule_int(rule1);
    game_life_model->add_Rule_int(rule2);
    game_life_model->add_Rule_int(rule3);
    game_life_model->add_Rule_int(rule4);

    Library::getLibrary()->add_Model(game_life_model);
}
int main(int argc, char *argv[])
{
    /*QApplication app(argc, argv);

    //Instantiate main window controller and display view
    C_MainWindow *mainWindowController = new C_MainWindow(&app);
    mainWindowController->init();

    // Show the view
    mainWindowController->getView()->show();

    return app.exec();*/

    ajout_donnee();
    Automate::getAutomate()->setModel(Library::getLibrary()->getListModels()->at(0));
    // J'affiche un surround (en croix)
    //Automate::getAutomate()->getModel()->getSurrounding()->afficher_surround();
    Automate::getAutomate()->init_Grid(5,5);
    // Après le init_Grid tout devient False
    //Automate::getAutomate()->getModel()->getSurrounding()->afficher_surround();
    Automate::getAutomate()->manual_init();
    Automate::getAutomate()->afficher_grid();
    cout<<endl;
    Automate::getAutomate()->next_generation();
    Automate::getAutomate()->afficher_grid();
    cout<<endl;
    Automate::getAutomate()->next_generation();
    Automate::getAutomate()->afficher_grid();
    cout<<endl;
    //Automate::getAutomate()->getModel()->getSurrounding()->afficher_surround();

    return 0;
}
