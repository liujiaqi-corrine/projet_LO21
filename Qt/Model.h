#ifndef MODEL_H_INCLUDED
#define MODEL_H_INCLUDED

class Model
{
    protected :
        string name;
        vector<State*>* listStates;
        Grid* grid;
    public :
        Model(string _name = "");
        ~Model() = default;

        string getName() const;
        vector<State*>* getListStates() const;
        Grid* getGrid() const;

        void setName(string _name);

        void init_Grid(int width, int length);
        void add_State(State* new_state);
        void del_State(State* _state);
};

#endif // MODEL_H_INCLUDED
