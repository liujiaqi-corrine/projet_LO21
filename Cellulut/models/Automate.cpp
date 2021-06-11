#include "main.h"
#include "models/Library.h"
#include "models/Grid.h"
#include "models/Automate.h"

Automate* Automate::singleton = new Automate;

Automate::Automate()
{
// Adding surroundings
    // von Neumann
    Library::getLibrary()->create_Surrounding("von Neumann");
    Library::getLibrary()->getListSurroundings()->at(0)->addInteraction({false, true, false});
    Library::getLibrary()->getListSurroundings()->at(0)->addInteraction({true, true, true});
    Library::getLibrary()->getListSurroundings()->at(0)->addInteraction({false, true, false});

    // Moore
    Library::getLibrary()->create_Surrounding("Moore");
    Library::getLibrary()->getListSurroundings()->at(1)->addInteraction({true, true, true});
    Library::getLibrary()->getListSurroundings()->at(1)->addInteraction({true, true, true});
    Library::getLibrary()->getListSurroundings()->at(1)->addInteraction({true, true, true});

// Adding models
    // Life Game
    Library::getLibrary()->create_Model("Life Game");
    State* dead = new State(0, "dead","white");
    State* alive = new State(1, "alive","black");
    Library::getLibrary()->getListModels()->at(0)->add_State(dead); // State dead added
    Library::getLibrary()->getListModels()->at(0)->add_State(alive); // State alive added
    Library::getLibrary()->getListModels()->at(0)->setSurrounding(Library::getLibrary()->getListSurroundings()->at(1)); // Surrounding set on Moore
    Rule_int* life_game_rule_1 = new Rule_int(1, 0, 0, 0); // Par défaut, une cellule devient morte
    Rule_int* life_game_rule_2 = new Rule_int(0, 3, 1, 1); // Une cellule morte avec 3 voisins vivants devient vivante
    Rule_int* life_game_rule_3 = new Rule_int(1, 2, 1, 1); // Une cellule vivante avec 2 voisins vivants devient vivante
    Rule_int* life_game_rule_4 = new Rule_int(1, 3, 1, 1); // Une cellule vivante avec 3 voisins vivants devient vivante
    Library::getLibrary()->getListModels()->at(0)->add_Rule_int(life_game_rule_1);
    Library::getLibrary()->getListModels()->at(0)->add_Rule_int(life_game_rule_2);
    Library::getLibrary()->getListModels()->at(0)->add_Rule_int(life_game_rule_3);
    Library::getLibrary()->getListModels()->at(0)->add_Rule_int(life_game_rule_4);

    // Brian's brain
    Library::getLibrary()->create_Model("Brian's brain");
    State* off = new State(0, "off","green");
    State* firing = new State(1, "firing","red");
    State* refractory = new State(2, "refractory","yellow");
    Library::getLibrary()->getListModels()->at(1)->add_State(off); // State off added
    Library::getLibrary()->getListModels()->at(1)->add_State(firing); // State firing added
    Library::getLibrary()->getListModels()->at(1)->add_State(refractory); // State refractory added
    Library::getLibrary()->getListModels()->at(1)->setSurrounding(Library::getLibrary()->getListSurroundings()->at(1)); // Surrounding set on Moore
    Rule_int* brians_brain_rule_1 = new Rule_int(1, 0, 0, 2); // Une cellule excitée devient réfractaire
    Rule_int* brians_brain_rule_2 = new Rule_int(2, 0, 0, 0); // Une cellule réfractaire devient au repos
    Rule_int* brians_brain_rule_3 = new Rule_int(0, 2, 1, 1); // Une cellule au repos avec 2 voisins excités devient excitée
    Library::getLibrary()->getListModels()->at(1)->add_Rule_int(brians_brain_rule_1);
    Library::getLibrary()->getListModels()->at(1)->add_Rule_int(brians_brain_rule_2);
    Library::getLibrary()->getListModels()->at(1)->add_Rule_int(brians_brain_rule_3);
}


Model* Automate::getModel() const{return this->model;}

vector<unsigned int**>* Automate::getHistoric() const{return this->historic;}


void Automate::setModel(Model* _model){this->model = _model;}

void Automate::init_Grid(unsigned int size)
{
    Grid::getGrid()->setSize(size);

    for (unsigned int i=0; i < size*size; i++)
    {
        Cell *cell = new Cell(i%size, i/size);
        cell->setState(this->model->getListStates()->at(0));
        Grid::getGrid()->getCells()->insert({cell->getHash(), cell});
    }

    qInfo() << "Automate::init_Grid - grid initialized with size of "<< size;
}

void Automate::save_current_config()
{
    unsigned int** saved_grid = new unsigned int*[Grid::getGrid()->getSize()];

    // Initialize saved_grid with current grid states index

    for (unsigned int i=0; i < Grid::getGrid()->getSize(); i++){
        saved_grid[i] = new unsigned int[Grid::getGrid()->getSize()];
        for (unsigned int j=0; j < Grid::getGrid()->getSize(); j++)
            saved_grid[i][j] = Grid::getGrid()->getCells()->at(Cell::getHashFromPos(i,j))->getState()->getIndex();
    }
    this->getHistoric()->push_back(saved_grid);
    return;
}

State* Automate::random_state() // Return random state in listStates
{
   static bool first = true;
   if (first)
   {
      srand( time(NULL) );
      first = false;
   }
   return this->getModel()->getListStates()->at(rand() % (this->getModel()->getListStates()->size()));
}



void Automate::manual_init()
{
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(0,0))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(0,1))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(0,2))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(0,3))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(0,4))->setState(this->model->getListStates()->at(0));

    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(1,0))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(1,1))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(1,2))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(1,3))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(1,4))->setState(this->model->getListStates()->at(0));

    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(2,0))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(2,1))->setState(this->model->getListStates()->at(1));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(2,2))->setState(this->model->getListStates()->at(1));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(2,3))->setState(this->model->getListStates()->at(1));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(2,4))->setState(this->model->getListStates()->at(0));

    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(3,0))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(3,1))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(3,2))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(3,3))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(3,4))->setState(this->model->getListStates()->at(0));

    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(4,0))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(4,1))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(4,2))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(4,3))->setState(this->model->getListStates()->at(0));
    Grid::getGrid()->getCells()->at(Cell::getHashFromPos(4,4))->setState(this->model->getListStates()->at(0));

    this->getHistoric()->clear();
    save_current_config();
}


void Automate::random_init()
{
    this->getHistoric()->clear();
    for (unsigned int i=0; i < Grid::getGrid()->getSize(); i++)
    {
        for (unsigned int j=0; j < Grid::getGrid()->getSize(); j++)
        {
            Grid::getGrid()->getCells()->at(Cell::getHashFromPos(i,j))->setState(random_state());
        }
    }
    return;
}

unsigned int Automate::count_nearby_state(unsigned int x, unsigned int y, unsigned int state_index)
{
    unsigned int k = 0;
    for (unsigned int i=0; i < 3; i++)
    {
        for(unsigned int j=0; j < 3; j++)
        {
            if (i==1 and j==1)
                continue;
            int row = x + i - 1;
            int column = y + j - 1;
            if (row < 0)
                row = Grid::getGrid()->getSize() - 1;
            else if (row == Grid::getGrid()->getSize())
                row = 0;
            if (column < 0)
                column = Grid::getGrid()->getSize() - 1;
            else if (column == Grid::getGrid()->getSize())
                column = 0;
            if (this->getModel()->getSurrounding()->getInteraction()->at(i*(this->getModel()->getSurrounding()->getRadius()*2+1) + j) and Grid::getGrid()->getCells()->at(Cell::getHashFromPos(row,column))->getState()->getIndex() == state_index)
                k += 1;
        }
    }
    return k;
}

unsigned int Automate::check_rule_int(unsigned int x, unsigned int y, unsigned int rule_int_index)
{
    Cell* current_cell = Grid::getGrid()->getCells()->at(Cell::getHashFromPos(x,y));
    Rule_int* current_rule = this->getModel()->getRule_int()->at(rule_int_index);
    if (current_cell->getState()->getIndex() == current_rule->getRule_current_state())
        if (!current_rule->getRule_nb_nearby() or count_nearby_state(x,y,current_rule->getRule_state_nearby()) == current_rule->getRule_nb_nearby())
            return 1;
    return 0;
}

unsigned int Automate::check_rule_ext(unsigned int x, unsigned int y, unsigned int rule_ext_index)
{
    Cell* current_cell = Grid::getGrid()->getCells()->at(Cell::getHashFromPos(x,y));
    Rule_ext* current_rule = this->getModel()->getRule_ext()->at(rule_ext_index);
    unsigned int current_radius = current_rule->getRadius();
    if (current_cell->getState()->getIndex() == current_rule->getCurrent_config()->at((current_radius*2+1)*current_radius+current_radius))
    {
        for (unsigned int i=0; i < current_radius*2+1; i++)
        {
            for(unsigned int j=0; j < current_radius*2+1; j++)
            {
                if (i==1 and j==1)
                    continue;
                int row = x + i - current_radius;
                int column = y + j - current_radius;
                if (row < 0)
                    row = Grid::getGrid()->getSize() - 1;
                else if (row == Grid::getGrid()->getSize())
                    row = 0;
                if (column < 0)
                    column = Grid::getGrid()->getSize() - 1;
                else if (column == Grid::getGrid()->getSize())
                    column = 0;
                if (Grid::getGrid()->getCells()->at(Cell::getHashFromPos(row,column))->getState()->getIndex() != current_rule->getCurrent_config()->at(i*(current_radius*2+1)+j))
                    return 0;
            }
        }
        return 1;
    }
    return 0;
}

void Automate::next_generation()
{
    cout<<"Next generation :"<<endl;
    // Initialize next_grid with values from current grid
    unsigned int** next_grid = new unsigned int*[Grid::getGrid()->getSize()];
        for (unsigned int i=0; i < Grid::getGrid()->getSize(); i++)
        {
            next_grid[i] = new unsigned int[Grid::getGrid()->getSize()];
            for (unsigned int j=0; j < Grid::getGrid()->getSize(); j++)
                next_grid[i][j] = Grid::getGrid()->getCells()->at(Cell::getHashFromPos(i,j))->getState()->getIndex();
        }

    // Check rules for each cell
        //Intentional rules
    if (this->model->getRule_int()->size())
        for (unsigned int i=0; i < Grid::getGrid()->getSize(); i++){
            for (unsigned int j=0; j < Grid::getGrid()->getSize(); j++)
            {
                for(unsigned int k = 0; k < this->model->getRule_int()->size(); k++)
                {
                    if (check_rule_int(i, j, k))
                        next_grid[i][j] = this->model->getRule_int()->at(k)->getRule_next_state();
                }
            }
        }
        // Extensional rules
    if (this->model->getRule_ext()->size())
        for (unsigned int i=0; i < Grid::getGrid()->getSize(); i++){
            for (unsigned int j=0; j < Grid::getGrid()->getSize(); j++)
            {
                for(unsigned int k = 0; k < this->model->getRule_ext()->size(); k++)
                {
                    if (check_rule_ext(i, j, k))
                        next_grid[i][j] = this->model->getRule_ext()->at(k)->getNext_state_index();
                }
            }
        }
    // Put new values in Grid
    for (unsigned int i=0; i < Grid::getGrid()->getSize(); i++)
    {
        for (unsigned int j=0; j < Grid::getGrid()->getSize(); j++)
        {
            Grid::getGrid()->getCells()->at(Cell::getHashFromPos(i,j))->setState(this->model->getListStates()->at(next_grid[i][j]));
        }
    }

    // Add next_grid to historic
    this->getHistoric()->push_back(next_grid);
    return;
}

void Automate::afficher_historique(int x)
{
    for (unsigned int i=0; i < Grid::getGrid()->getSize(); i++){
        for (unsigned int j=0; j < Grid::getGrid()->getSize(); j++)
            cout<<this->getHistoric()->at(x)[i][j]<<" ";
        cout<<endl;
        }
    cout<<endl;
}

void Automate::afficher_grid()
{
    cout<<"Affichage grid :"<<endl;
    for (unsigned int i=0; i < Grid::getGrid()->getSize(); i++){
        for (unsigned int j=0; j < Grid::getGrid()->getSize(); j++)
            cout<<Grid::getGrid()->getCells()->at(Cell::getHashFromPos(i,j))->getState()->getIndex()<<" ";
        cout<<"\n";
    }
}
