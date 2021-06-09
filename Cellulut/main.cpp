#include "main.h"

#include <QApplication>
#include "data/DataEngine.h"
#include "ui/UIEngine.h"
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
    Surrounding* game_life_surround = new Surrounding(0,"Jeu de la vie");
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

    DataEngine *dataEngine = new DataEngine();
    UIEngine *uiEngine = new UIEngine(&app);

    uiEngine->setInsideDataForUI(dataEngine->getInsideDataForUI());
    dataEngine->setInsideUIForData(uiEngine->getInsideUIForData());

    uiEngine->start();
    uiEngine->changeToSimulationView();

    return app.exec();*/

    ajout_donnee();
    Automate::getAutomate()->setModel(Library::getLibrary()->getListModels()->at(0));
    Automate::getAutomate()->init_Grid(5,5);
    Automate::getAutomate()->manual_init();

    Automate::getAutomate()->afficher_grid();
    cout<<endl;
    Automate::getAutomate()->next_generation();
    Automate::getAutomate()->afficher_grid();
    cout<<endl;
    Automate::getAutomate()->next_generation();
    Automate::getAutomate()->afficher_grid();
    cout<<endl;
    cout<<"Historic :"<<endl;
    Automate::getAutomate()->afficher_historique(0);
    Automate::getAutomate()->afficher_historique(1);
    Automate::getAutomate()->afficher_historique(2);

    return 0;
}
