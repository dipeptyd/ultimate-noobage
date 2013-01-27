//  a b c d e f g h i j k l m n o p q r s t u v w x y z
//
// LoremipsumdolorsitametconsecteturadipiscingelitPhaselluselementumultricesmagnasedvulputatemiinterdumaMorbipulvinarquamsitamettristiqueporttitororciurnaconvallisligulaatgravidaodionibhsitametodioInsedurnaquismivariuspulvinarFuscemolestienuncerosidimperdietrisusDoneclectusauguesemperidmolestiefringillamolestieetpurusFusceornaretortorvitaenisiultricesvitaeultricesduiconsecteturSedateratorciMorbiporttitoramet
//
// 
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;
const int buf_size = 255;
struct node 
{
    node *left;
    node *right;
    unsigned counter;
    char *name;
    node(const char *str, unsigned counter=1):counter(counter),name(NULL),left(NULL),right(NULL)
    {
        this->name = new char[strlen(str)+1];
        strcpy(name, str);
    }
    ~node()
    {
        delete[] name;
    }


};

class tree
{
    std::ifstream *file;
    void add_to_tree(const char *str);
    void add_node_to_tree(const node *n);
    void add_tree_to_tree(const tree &t);

    protected:
        node *root;
    public:

    ~tree();
    void tree_dest(node *iter);

    tree(const tree &some_tree);
    tree(ifstream &file);
    tree();

    void noobtraverse(node *iter);
    void load_file(ifstream &file);

};


tree::tree()
{
}

tree::tree(const tree &some_tree)
{
    this->add_tree_to_tree(some_tree);
}

void tree::add_tree_to_tree(const tree &t)
{
    node *foreign_iter = t.root;
    if(foreign_iter)
    {

    }

}

void tree::add_node_to_tree(const node *n)
{
    node *iter = root;

    while(iter)
    {
        int str_cmp = strcmp(n->name, iter->name);
        if(str_cmp==0)
        {
            iter->counter += n->counter;
            return;
        }
        else if(str_cmp>0)
        {
            if(iter->left)
                iter=iter->left;
            else
            {
                iter->left = new node(n->name, n->counter);
            }
        }
        else
        {
            if(iter->right)
            {
                iter=iter->right;
            }
            else
            {
                iter->right = new node(n->name,n->counter);
            }
        }
    }
}

void tree::add_to_tree(const char *str)
{
    short str_cmp;
    node *iter = root;
    while(iter)
    {
        str_cmp = strcmp(str,iter->name);

        if(str_cmp==0)
        {
            iter->counter++;
            return;
        }
        else if(str_cmp>0)
        {
            if(iter->left)
                iter=iter->left;
            else
            {
                iter->left = new node(str);
                return;
            }
        }
        else
        {
            if(iter->right)
                iter=iter->right;
            else
            {
                iter->right = new node(str);
                return;
            }
        }


    }
    root = new node(str);
}

void tree::tree_dest(node *iter)
{
    if(iter->right)
    {
        this->tree_dest(iter->right);
    }
    if(iter->left)
    {
        this->tree_dest(iter->left);
    }
    delete iter;
}

tree::~tree(){
    this->tree_dest(this->root);
}

void tree::load_file(ifstream &file)
{
    char *buffer = new char[buf_size];
    char *buffer_end = buffer+buf_size;
    
    this->file = &file;
    

    char chb;

    while(file)
    {
        file.get(chb);
        if(isalpha(chb))
        {
            char *p_bfr = buffer;
            while(isalpha(chb))
            {
                if(p_bfr==buffer_end)
                    break;

                *(p_bfr++) = chb;
                file.get(chb);
            }
                *p_bfr = '\0';
                this->add_to_tree(buffer);

        }

    }
    this->noobtraverse(this->root);
    delete[] buffer;

}

tree::tree(ifstream &file):root(NULL)
{
    this->load_file(file);
}

void tree::noobtraverse(node *iter)
{
    //http://en.wikipedia.org/wiki/Tree_traversal#Depth-first_2
    cout << "name " << iter->name << endl;
    cout << "counter " << iter->counter << endl;
    if(iter->right)
        this->noobtraverse(iter->right);
    if(iter->left)
        this->noobtraverse(iter->left);
}


class amount_sort_tree : public tree
{
    void add_node_to_tree(node *n);
};

void amount_sort_tree::add_node_to_tree(node *n)
{
    
}

int main()
{
    std::ifstream file("tree.cpp");

    if(file.good())
        tree f(file);

    return 0;
}
