#include "main.h"

int main()
{
    /*Model* model_test = new Model("test");
    State* vivant = new State("vivant","black",1);
    State* mort = new State("mort","white",1);
    model_test->add_State(vivant);
    try{model_test->add_State(mort);}
    catch(exception const& except)
    {cerr<<"ERREUR : "<<except.what()<<endl;}*/


    /*//Manipulation de la bibliothèque
    Model* model1 = new Model("model1"); //Initialisation de 3 modèles
    Model* model2 = new Model("model2");
    Model* model3 = new Model("model3");
    Library::getInstance()->add_Model(model1); //Ajout des 3 modèles à la bibliothèque
    Library::getInstance()->add_Model(model2);
    Library::getInstance()->add_Model(model3);
    try{Library::getInstance()->add_Model(model1); //Ajout redondant}
    catch(exception const& except)
    {cerr<<"ERREUR : "<<except.what()<<endl;}
    cout<<Library::getInstance()->getListModels()->size()<<endl;             //Taille de la biblio
    cout<<Library::getInstance()->getListModels()->at(2)->getName()<<endl;  //Nom du troisieme modele
    Library::getInstance()->del_Model(model1);                             //Suppression du modele 1
    cout<<Library::getInstance()->getListModels()->at(0)->getName()<<endl;//Nom du premier modele
    */

    /*//Initaliser un modèle avec une grille 3x5 et ajout de l'état "dead"
    Model* model = new Model();
    model->init_Grid(3,5);
    State* dead = new State("dead","black",1);
    try
    {
        model->add_State(dead);
    }
    catch(exception const& except)
    {
        cerr<<"ERREUR : "<<except.what()<<endl;
    }
    model->getGrid()->getlistCells()[1][3].setState(model->getListStates()->at(1));
    for(int i = 0; i< model->getGrid()->getWidth(); i++)
    {
        for(int j = 0; j< model->getGrid()->getLength(); j++)
        {
            cout<<model->getGrid()->getlistCells()[i][j].getState()->getLabel();
            cout<<model->getGrid()->getlistCells()[i][j].getX();
            cout<<model->getGrid()->getlistCells()[i][j].getY()<<" ";
        }
        cout<<endl;
    }*/

    cout<<"\nDone"<<endl;
    //system("pause");
    return 0;
}
