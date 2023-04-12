#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>

class ICalculatable
{

public:

    virtual double Calculate() = 0;
    virtual bool HasRightChild() = 0;
    virtual void SetRightChild(std::unique_ptr<ICalculatable> node) = 0;
    virtual ~ICalculatable()
    {};

protected:

    ICalculatable()
    {};

};


class Plus: public ICalculatable
{

public:

    Plus(std::unique_ptr<ICalculatable> left = nullptr, std::unique_ptr<ICalculatable> right = nullptr);
    double Calculate() override;
    bool HasRightChild() override;
    void SetRightChild(std::unique_ptr<ICalculatable> node) override;

private:

    std::unique_ptr<ICalculatable> left_child_;
    std::unique_ptr<ICalculatable> right_child_;
};

class Minus: public ICalculatable
{

public:

    Minus(std::unique_ptr<ICalculatable> left = nullptr, std::unique_ptr<ICalculatable> right = nullptr);  
    double Calculate() override;
    bool HasRightChild() override;
    void SetRightChild(std::unique_ptr<ICalculatable> node) override;

private:

    std::unique_ptr<ICalculatable> left_child_;
    std::unique_ptr<ICalculatable> right_child_;

};

class Bracket: public ICalculatable
{

public:

    Bracket(const std::vector<std::string>& vec, const int pos, int& pos_end);
    double Calculate() override;

private:

    bool HasRightChild() override;
    void SetRightChild(std::unique_ptr<ICalculatable> node);
    std::unique_ptr<ICalculatable> expres_;

};

class Number: public ICalculatable
{

public:

    Number()
        :   numb_(0)
        {};

    explicit Number(double numb)
        :   numb_(numb)
        {};

    double Calculate() override;

private:

    bool HasRightChild() override;
    void SetRightChild(std::unique_ptr<ICalculatable> node) override;
    double numb_;
};

class Delet : public ICalculatable
{

public:

    Delet(std::unique_ptr<ICalculatable> left = nullptr, std::unique_ptr<ICalculatable> right = nullptr);
    double Calculate() override;
    bool HasRightChild() override;
    void SetRightChild(std::unique_ptr<ICalculatable> node) override;

private: 

    std::unique_ptr<ICalculatable> left_child_;
    std::unique_ptr<ICalculatable> right_child_;

};

class Floor : public ICalculatable
{

public:

    Floor(const std::vector<std::string>& vec, const int pos, int& pos_end);
    double Calculate() override;

private:

    bool HasRightChild() override;
    void SetRightChild(std::unique_ptr<ICalculatable> node) override;
    std::unique_ptr<ICalculatable> expres_;
    
};

class Round : public ICalculatable
{

public:

    Round(const std::vector<std::string>& vec, const int pos, int& pos_end);
    double Calculate() override;

private: 
    
    bool HasRightChild() override;
    void SetRightChild(std::unique_ptr<ICalculatable> node) override;
    std::unique_ptr<ICalculatable> expres_;
    
};

const char plus_sign = '+';
const char minus_sign = '-';
const char open_bracket_sign = '(';
const char closed_bracket_sign = ')';
const char delete_sign = '/';
const char floor_sign = 'f';
const char round_sign = 'r';

void parse_arguments(int argc, char** argv, std::vector<std::string>& vec);
double solve_expression(std::vector<std::string>& vec);
void add_brackets(std::vector<std::string>& vec);
