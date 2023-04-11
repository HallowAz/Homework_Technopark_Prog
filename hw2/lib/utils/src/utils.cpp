#include "utils.hpp"
#include <sstream>
#include <iostream>

void parse_arguments(int argc, char** argv, std::vector<std::string>& vec)
{
    std::istringstream stream_string(argv[1]);
    std::string tok;

    while (stream_string >> tok)
        vec.push_back(tok);

}

Plus::Plus(std::unique_ptr<ICalculatable> left, std::unique_ptr<ICalculatable> right)
{
    left_child_ = std::move(left);
    right_child_ = std::move(right);
}

double Plus::Calculate()
{
    return left_child_.get()->Calculate() + right_child_.get()->Calculate();
}

Minus::Minus(std::unique_ptr<ICalculatable> left, std::unique_ptr<ICalculatable> right)
{
    left_child_ = std::move(left);
    right_child_ = std::move(right);
}

double Minus::Calculate()
{
    return left_child_.get()->Calculate() - right_child_.get()->Calculate();
}

double solve_expression(std::vector<std::string>& vec)
{
    int pos = 0;
    std::unique_ptr<ICalculatable> root;
    
    if ( vec[0][0] == '(')
    {
        Bracket brack(vec, 1);
            
        pos = brack.GetPosOfEnd(); 
             
        root = std::make_unique<Number>(brack.Calculate());
            
    }
    else
        root = std::make_unique<Number>(std::stod(vec[0]));
    
    pos++;

    for (int i = pos; i < std::size(vec); i++)
    {
        //std::cout << "Solve" << std::endl;
      //  std::cout << vec[i] << std::endl;
        if (vec[i][0] == '+')
        {
            std::unique_ptr<ICalculatable> node = std::make_unique<Plus>(std::move(root));
            std::swap(root, node);
        }
        else if (vec[i][0] == '-')
        {
            std::unique_ptr<ICalculatable> node = std::make_unique<Minus>(std::move(root));
            std::swap(root, node);
        }

        else if (vec[i][0] == '(')
        {
            Bracket brack(vec, i + 1);
            //std::cout << "Hello pos" << std::endl;
            i = brack.GetPosOfEnd(); 
            // i = brack.GetPosOfEnd();
            //std::cout << typename(brack) << std::endl; 
            std::unique_ptr<ICalculatable> node = std::make_unique<Number>(brack.Calculate());
            root.get()->SetRightChild(std::move(node));
            //std::cout << "Hello" << std::endl;
            
        }

        else
        {
            //std::cout << "Hello"  << ' ' << vec[i]<< std::endl;
            std::unique_ptr<ICalculatable> node = std::make_unique<Number>(std::stod(vec[i]));
            root.get()->SetRightChild(std::move(node));
        }
    }

    return root.get()->Calculate();
}

bool Plus::HasRightChild()
{
    return right_child_ != nullptr;
}

bool Minus::HasRightChild()
{
    return right_child_ != nullptr;
}

bool Number::HasRightChild()
{
    return false;
}


Bracket::Bracket(const std::vector<std::string>& vec, const int pos)
{
    std::vector<std::string> new_vec;
    size_t count_of_brackets = 1;
    for (int i = pos;  count_of_brackets != 0; i++)
    {
        if (vec[i][0] == ')')
        {
            --count_of_brackets;
            pos_of_end_ = i;
        }
        else if (vec[i][0] == '(')
            ++count_of_brackets;

        if (count_of_brackets != 0)
        {
            new_vec.push_back(vec[i]);

        }

    }


    // for (int i = 0; i < new_vec.size(); i++)
    // {
    //     std::cout << new_vec[i] << std::endl;
    //     std::cout << std::endl;
    // }
   // std::cout << ++pos_of_end_ << std::endl;
    expres_ = std::make_unique<Number>(solve_expression(new_vec));
}

bool Bracket::HasRightChild()
{
    return false;
}

int Bracket::GetPosOfEnd()
{
    return pos_of_end_;
}

void Bracket::SetRightChild(std::unique_ptr<ICalculatable> node){
    return;
}

double Bracket::Calculate()
{   
    return expres_.get()->Calculate();
}

double Number::Calculate()
{
    return numb_;
}

void Plus::SetRightChild(std::unique_ptr<ICalculatable> node)
{
    right_child_ = std::move(node);
}

void Minus::SetRightChild(std::unique_ptr<ICalculatable> node)
{
    right_child_ = std::move(node);
}

void Number::SetRightChild(std::unique_ptr<ICalculatable> node)
{
    return;
}


// double solve_expression(std::vector<std::string> & vec)
// {
//     double res = 0;

//     for (int i  = 0; i < std::size(vec); i++)
//     {
//         ICalculatable* oper;
//         switch (vec[0][0])
//         {
//             case '+':
                
//                 break;
//             case '-':
//                 Minus oper;

//         }    
//     }
// }

// Node::Node(std::unique_ptr<ICalculatable> current, std::unique_ptr<ICalculatable> left, std::unique_ptr<ICalculatable> right)
// {
//     current_ = std::move(current);
//     left_ = std::move(left);
//     right_ = std::move(right);
    
// }

// // Node & Node::operator = (Node && orig)
// // {
// //     current_ = std::move(orig.current_);
// //     left_ = std::move(orig.left_);
// //     right_ = std::move(orig.right_);
// //     return *this;
// // }

// Tree::Tree(std::unique_ptr<Node> root)
// {
//     root_ = std::move(root);
// }

// void Tree::Add(std::unique_ptr<Node> node)
// {
//     if (root_)
//     {
//         root_ = std::make_unique<Node>(node);       
//         return;
//     }

    
//     while (root_.get().
//     node_ = std::make_unique<Node>(node);

    
// }