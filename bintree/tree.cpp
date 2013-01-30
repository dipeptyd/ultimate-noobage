#include <fstream>
#include <iostream>
#include <cstring>
#include "node.hpp"
using namespace std;

std::ofstream outlog("outlog");
std::ostream& output = std::cout;
const int buf_size = 255;

class tree
{
    std::ifstream *file;
    void add_to_tree(const char *str);

    void rotate_left(node *n);
    void rotate_right(node *n);

    protected:
        node *root;
    public:

    ~tree();
    void tree_dest(node *iter);

    tree(ifstream &file);
    tree();
    void noobtraverse(node *iter);
    void print_tree(node *iter);
    void print_tree();
    void load_file(ifstream &file);
    void balance_branch(node *iter);
    int branch_ratio(node *iter);
    unsigned branch_size(node *iter, const bool &reset=false, const int &other_branch =-1);
    int branch_height(node *iter);
    unsigned branch_depth(node *iter);
    void print_node(node *n);


};



void tree::print_node(node *n)
{
    if(n)
    {
    output << n << std::endl;
    if(n->parent)
        output << "parent:" << n->parent << std::endl;

    output << "name  :" << n->name << std::endl;

    if(n->left)
        output << "left  :" << n->left->name << std::endl;
    if(n->right)
        output << "right :" << n->right->name << std::endl;
    }


}

unsigned tree::branch_depth(node *iter)
{
    if(iter)
    return(1+branch_depth(iter->parent));
    else
        return -1;

}

void tree::print_tree()
{
    this->noobtraverse(this->root);
}

void tree::print_tree(node *n)
{

}

void tree::rotate_left(node *n) // rotate_left because the n node goes to the left
{

    node *a, *b, *c, *par; // yes, i'm too stupid to do this right.

    a = n;
    b = n->right;
    if(b)
        c = b->right;
    par = n->parent;


    outlog << "=============================ROTATE_LEFT======================================" << std::endl;
    outlog << "================================PRE===========================================" << std::endl;
    outlog << "a " << a << std::endl << "  " <<  a->parent << " " << a->left << " " << a->right << std::endl;
    outlog << "b " << b << std::endl << "  " <<  b->parent << " " << b->left << " " << b->right << std::endl;
    if(c)
        outlog << "c " << c << std::endl << "  " <<  c->parent << " " << c->left << " " << c->right << std::endl;
    outlog << "==============================================================================" << std::endl;
    if(par)
        if(par->left == a)
            par->left = b;
        else
            par->right = b;
    else
        this->root=b;

    b->parent = par;

    a->right = b->left;
    b->left = a;
    a->parent = b;


    outlog << "===============================POST===========================================" << std::endl;
    outlog << "a " << a << std::endl << "  " <<  a->parent << " " << a->left << " " << a->right << std::endl;
    outlog << "b " << b << std::endl << "  " <<  b->parent << " " << b->left << " " << b->right << std::endl;
    if(c)
        outlog << "c " << c << std::endl << "  " <<  c->parent << " " << c->left << " " << c->right << std::endl;
    outlog << "==============================================================================" << std::endl;
}
void tree::rotate_right(node *n)
{

    node *a, *b, *c, *par; // yes, i'm too stupid to do this right.

    a = n;
    b = n->left;
    if(b)
        c = b->left;

    par = n->parent;

    outlog << "=============================ROTATE_RIGHT=====================================" << std::endl;
    outlog << "================================PRE===========================================" << std::endl;
    outlog << "a " << a << std::endl << "  " <<  a->parent << " " << a->left << " " << a->right << std::endl;
    outlog << "b " << b << std::endl << "  " <<  b->parent << " " << b->left << " " << b->right << std::endl;
    if(c)
        outlog << "c " << c << std::endl << "  " <<  c->parent << " " << c->left << " " << c->right << std::endl;
    outlog << "==============================================================================" << std::endl;

    if(par)
        if(par->left == a)
            par->left = b;
        else
            par->right = b;
    else
        this->root = b;
    b->parent = par;

    a->left = b->right;
    b->right = a;
    a->parent = b;


    outlog << "===============================POST===========================================" << std::endl;
    outlog << "a " << a << std::endl << "  " <<  a->parent << " " << a->left << " " << a->right << std::endl;
    outlog << "b " << b << std::endl << "  " <<  b->parent << " " << b->left << " " << b->right << std::endl;
    if(c)
        outlog << "c " << c << std::endl << "  " <<  c->parent << " " << c->left << " " << c->right << std::endl;
    outlog << "==============================================================================" << std::endl;

}
int tree::branch_height(node *iter)
{
    if(iter)
        return (max(branch_height(iter->left), branch_height(iter->right)+1));
    else 
        return -1;

}

int tree::branch_ratio(node *iter)
{

    int ratio = 0;
    if(iter)
    {
        unsigned left = this->branch_height(iter->left);
        unsigned right = this->branch_height(iter->right); //static doesn't 0 ? >:
        ratio = (left-right);
    }

    return ratio;

}

unsigned tree::branch_size(node *iter, const bool &reset, const int &other_branch)
{


    static unsigned counter = 0;
    if(reset)
        counter = 0;
    //outlog << " ohai counter is " << counter << std::endl;
    if(iter)
    {
        ++counter;

        if(other_branch != -1 and counter > other_branch)
        {
            return counter;
        }

            branch_size(iter->left, false, other_branch);
            branch_size(iter->right, false, other_branch);
    }


    return counter;
}

tree::tree()
{
}


void tree::balance_branch(node *iter)
{
    if(iter)
    {

    int ratio = this->branch_ratio(iter);

    outlog << ratio << std::endl;  //below 0  - right branch larger

        ////
    if(ratio == 2 or ratio == -2)
    {

                //output << "====================================================================" <<std::endl;
                //this->print_tree();
        int child_ratio;
        if(ratio == 2)
        {

            outlog << "LEFT " << std::endl;

            child_ratio = this->branch_ratio(iter->left);
            outlog << child_ratio;
                if(child_ratio>0)
                {
                    outlog << "LEFT LEFT" << std::endl;
                    this->rotate_right(iter);

                }

                else if(child_ratio<0)
                {
                    outlog <<"LEFT RIGHT ROTATION" << std::endl;

                    this->rotate_left(iter->left);
                    this->rotate_right(iter);
                }
                else
                {
                    outlog << "DUNNOLOL ROTATION" << std::endl;
                }

        }
        if(ratio == -2)
        {
            outlog << "RIGHT ROTATION" << std::endl;

            child_ratio = this->branch_ratio(iter->right);
            outlog << child_ratio;
                if(child_ratio>0)
                {
                    outlog << "RIGhT LEFT ROTATION" << std::endl;
                    this->rotate_right(iter->right);
                    this->rotate_left(iter);
                }
                else if(child_ratio<0)
                {
                    outlog <<"RIGHT RIGHT ROTATION" << std::endl;
                    this->rotate_left(iter);
                }
                else
                    outlog << "DUNNOLOL ROTATION" << std::endl;
        }

                //output << "====================================================================" <<std::endl;
                //this->print_tree();
    }
    else
    {
            outlog << "GOIN UP" << std::endl;
            this->balance_branch(iter->parent);
    }


    }
}

void tree::add_to_tree(const char *str)
{
    
    bool borked = false;

    if(strcmp(str, "sagittis")==0)
           {

               borked = true;
               cout << "======================================" << std::endl;

           }
    short str_cmp;
    node *iter = root;
    while(iter)
    {
        str_cmp = strcmp(str,iter->name);

        if(borked)
            print_node(iter);

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
                iter->left->parent = iter; //TODO: node method instead?
                if(borked)
                    output <<  " ADD TO RIGHT" << std::endl;
                this->balance_branch(iter);
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
                iter->right->parent = iter; //TODO: node method instead?
                if(borked)
                    output <<" ADD TO RIGHT" << std::endl;
                this->balance_branch(iter);
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
    outlog << " ratio " << this->branch_ratio(this->root) << std::endl;
    delete[] buffer;

}

tree::tree(ifstream &file):root(NULL)
{
    this->load_file(file);
}

void tree::noobtraverse(node *iter)
{
    if(iter)
    {
        this->noobtraverse(iter->right);
        output << this->branch_depth(iter) << " :" << "(" << iter->name << ")";
            if(iter->parent)
                output << "[" <<  iter->parent->name << "]" << std::endl;
            else
                output << std::endl;
        this->noobtraverse(iter->left);
    }
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
    std::ifstream file("testfile");

    if(file.good())
        tree f(file);

    return 0;
}
