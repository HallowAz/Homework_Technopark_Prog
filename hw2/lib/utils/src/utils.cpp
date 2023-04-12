#include "utils.hpp"
#include <sstream>
#include <iostream>
#include <vector>


void parse_arguments(int argc, char** argv, std::vector<std::string>& vec)
{
    std::istringstream stream_string(argv[1]);
    std::string tok;

    while (stream_string >> tok)
        vec.push_back(tok);

    add_brackets(vec);
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
        root = std::make_unique<Number>(Bracket(vec, 1, pos).Calculate());
    }

    else if (vec[0] == "floor")
    {
        root = std::make_unique<Number>(Floor(vec, 1, pos).Calculate());
    }

    else if (vec[0] == "round")
    {
        root = std::make_unique<Number>(Round(vec, 1, pos).Calculate());
    }

    else
        root = std::make_unique<Number>(std::stod(vec[0]));

    pos++;

    for (int i = pos; i < std::size(vec); i++)
    {

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

        else if (vec[i][0] == '/')
        {
            std::unique_ptr<ICalculatable> node = std::make_unique<Delet>(std::move(root));
            std::swap(root, node);
        }

        else if (vec[i][0] == '(')
        {
            std::unique_ptr<ICalculatable> node = std::make_unique<Number>(Bracket(vec, i + 1, i).Calculate());
            root.get()->SetRightChild(std::move(node));
        }

        else if (vec[i] == "floor")
        {
            std::unique_ptr<ICalculatable> node = std::make_unique<Number>(Floor(vec, i + 2, i).Calculate());
            root.get()->SetRightChild(std::move(node));
        }

        else if (vec[i] == "round")
        {
            std::unique_ptr<ICalculatable> node = std::make_unique<Number>(Round(vec, i + 2, i).Calculate());
            root.get()->SetRightChild(std::move(node));
        }

        else
        {
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


Bracket::Bracket(const std::vector<std::string>& vec, const int pos, int& pos_end)
{
    std::vector<std::string> new_vec;
    size_t count_of_brackets = 1;
    for (int i = pos;  count_of_brackets != 0; i++)
    {
        if (vec[i][0] == ')')
        {
            --count_of_brackets;
            pos_end = i;
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

Delet::Delet(std::unique_ptr<ICalculatable> left, std::unique_ptr<ICalculatable> right)
{
    left_child_ = std::move(left);
    right_child_ = std::move(right);
}

double Delet::Calculate()
{
    return left_child_.get()->Calculate() / right_child_.get()->Calculate();
}

bool Delet::HasRightChild()
{
    return right_child_ != nullptr;
}

void Delet::SetRightChild(std::unique_ptr<ICalculatable> node)
{
    right_child_ = std::move(node);
}

void add_brackets_just_number(std::vector<std::string>& vec, std::vector<std::string>& new_vec, const int index_new, const int index_old)
{
    if (vec[index_old - 1][0] != ')' && vec[index_old + 1][0] != '(') 
    {
        new_vec.insert(new_vec.begin() + index_new - 1, "(");
        vec.insert(vec.begin() + index_old + 2, ")");
    }

    else if (vec[index_old - 1][0] == ')' && vec[index_old + 1][0] != '(')
    {
        int bracket_index = std::size(new_vec) - 1;
        for (int bracket_count = 1; bracket_count != 0;)
        {
            bracket_index--;
            if (new_vec[bracket_index][0] == '(')
                bracket_count--;
            else if (new_vec[bracket_index][0] == ')')
                bracket_count++;
        }
        if (bracket_index <= 0)
            new_vec.insert(new_vec.begin(), "(");    
        else
            new_vec.insert(new_vec.begin() + bracket_index, "(");
        vec.insert(vec.begin() + index_old + 2, ")");

    }

}

void add_brackets(std::vector<std::string>& vec)
{
    std::vector<std::string> new_vec;
    for (int i = 0; i < std::size(vec); i++)
    {
        if ( vec[i][0] == '/')
        {
            add_brackets_just_number(vec, new_vec, std::size(new_vec), i);
        }
        
        new_vec.push_back(vec[i]);
    }

    for (int i = 0; i < std::size(new_vec); i++)
    {
        std::cout << new_vec[i] << std::endl;
    }
    
    vec = new_vec;

}

Floor::Floor(const std::vector<std::string>& vec, const int pos, int& pos_end)
{
    std::vector<std::string> new_vec;
    size_t count_of_brackets = 1;
    for (int i = pos;  count_of_brackets != 0; i++)
    {
        if (vec[i][0] == ')')
        {
            --count_of_brackets;
            pos_end = i;
        }
        else if (vec[i][0] == '(')
            ++count_of_brackets;

        if (count_of_brackets != 0)
        {
            new_vec.push_back(vec[i]);

        }

    }

    expres_ = std::make_unique<Number>(solve_expression(new_vec));
}

double Floor::Calculate()
{
    return floor(expres_.get()->Calculate());
}

bool Floor::HasRightChild()
{
    return false;
}

void Floor::SetRightChild(std::unique_ptr<ICalculatable> node)
{
    return;
}

int Floor::GetPosOfEnd()
{
    return pos_of_end_;
}

Round::Round(const std::vector<std::string>& vec, const int pos, int& pos_end)
{
    std::vector<std::string> new_vec;
    size_t count_of_brackets = 1;
    for (int i = pos;  count_of_brackets != 0; i++)
    {
        if (vec[i][0] == ')')
        {
            --count_of_brackets;
            pos_end = i;
        }
        else if (vec[i][0] == '(')
            ++count_of_brackets;

        if (count_of_brackets != 0)
        {
            new_vec.push_back(vec[i]);

        }

    }

    expres_ = std::make_unique<Number>(solve_expression(new_vec));
}

double Round::Calculate()
{
    return round(expres_.get()->Calculate());
}

bool Round::HasRightChild()
{
    return false;
}

void Round::SetRightChild(std::unique_ptr<ICalculatable> node)
{
    return;
}

int Round::GetPosOfEnd()
{
    return pos_of_end_;
}
