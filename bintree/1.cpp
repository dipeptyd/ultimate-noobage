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
    node(const char *str):counter(1),name(NULL),left(NULL),right(NULL)
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
    unsigned size;
    node *root;
    std::ifstream *file;
    void add_to_tree(const char *str);
    public:
    ~tree();
    tree(ifstream &file);
    tree();
    void noobtraverse(node *iter);
    void noobtraverse_dest(node *iter);
    void tree_count(node *head);
    //void tree_size(node *node, unsigned &count);
    void resort();

};


void tree::resort()
{

}


void tree::tree_size(node *node, unsigned &count)
{
    ++count;
    if(node->left)
        tree_size(node->left, count);
    if(node->right)
        tree_size(node->right,count);

}


tree::tree()
{

}

void tree::tree_count(node *head)
{

    //tree fb();

    //fb.tree_size(head);
    //tree newtree();

    //fb.resort(this);


    //unsigned left_side;
    //tree_size(head->left, left_side);
    //unsigned right_side;
    //tree_size(head->right, right_side);
    //cout << "left side " << left_side << std::endl;
    //cout << "right side " << right_side << std::endl;

    //node *level_1;
    //node *level_2;

    //if(left_side>right_side)
    //{
    ////level_1 = head->left;
    ////level_2 = level_1->left;
    ////level_2->right = head;
    //}

    //tree_size(head, size);
    //std::cout << size << std::endl;



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

void tree::noobtraverse_dest(node *iter)
{
    if(iter->right)
    {
        this->noobtraverse_dest(iter->right);
    }
    if(iter->left)
    {
        this->noobtraverse_dest(iter->left);
    }
    delete iter;
}

tree::~tree(){
    this->noobtraverse_dest(this->root);
}

tree::tree(ifstream &file):root(NULL)
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

    this->tree_count(root);

}

void tree::noobtraverse(node *iter)
{
    //cout << "parent" << iter->parent << endl;
    cout << "name " << iter->name << endl;
    cout << "counter " << iter->counter << endl;
    if(iter->right)
        this->noobtraverse(iter->right);
    if(iter->left)
        this->noobtraverse(iter->left);
}


int main()
{
    std::ifstream file("1.cpp");

    tree f(file);

    //tree newtree;
    //newtree.resort();

    return 0;
}
