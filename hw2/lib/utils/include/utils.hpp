#pragma once
#include <iostream>
#include <vector>
#include <memory>

class ICalculatable
{
public:   
    virtual double Calculate() = 0;
    virtual bool HasRightChild() = 0;
    virtual void SetRightChild(std::unique_ptr<ICalculatable> node) = 0;
    //virtual void SetLeftChild(std::unique_ptr<ICalculatable> node) = 0; 
    // virtual std::unique_ptr<ICalculatable> GetLeftChild() = 0;
    // virtual std::unique_ptr<ICalculatable> GetRightChild() = 0;
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
    //void SetLeftChild(std::unique_ptr<ICalculatable> node) override;
    // std::unique_ptr<ICalculatable> GetLeftChild() override;
    // std::unique_ptr<ICalculatable> GetRightChild() override;
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
  //  void SetLeftChild(std::unique_ptr<ICalculatable> node) override;
    // std::unique_ptr<ICalculatable> GetLeftChild() override;
    // std::unique_ptr<ICalculatable> GetRightChild() override;

private:
    std::unique_ptr<ICalculatable> left_child_;
    std::unique_ptr<ICalculatable> right_child_;

};

class Bracket: public ICalculatable
{

public:
    Bracket(const std::vector<std::string>& vec, const int pos);
    double Calculate() override;
    bool HasRightChild() override;
    void SetRightChild(std::unique_ptr<ICalculatable> node);
    int GetPosOfEnd();
   // void SetLeftChild(std::unique_ptr<ICalculatable> node) override;
    // std::unique_ptr<ICalculatable> GetLeftChild() override;
    // std::unique_ptr<ICalculatable> GetRightChild() override;

private:
    int pos_of_end_;
    std::unique_ptr<ICalculatable> expres_;
};

class Number: public ICalculatable
{
public:
    Number()
        :   numb_(0)
        {};

    Number(double numb)
        :   numb_(numb)
        {};

    double Calculate() override;
    bool HasRightChild() override;
    void SetRightChild(std::unique_ptr<ICalculatable> node) override;
    //void SetLeftChild(std::unique_ptr<ICalculatable> node) override;
    // std::unique_ptr<ICalculatable> GetLeftChild() override;
    // std::unique_ptr<ICalculatable> GetRightChild() override;

private:
    double numb_;
};

// struct Node
// {
//     Node()
//         :   current_(nullptr),
//             left_(nullptr),
//             right_(nullptr)
//             {};
    
//     Node(std::unique_ptr<ICalculatable> current, std::unique_ptr<ICalculatable> left, std::unique_ptr<ICalculatable> right);
    
//     std::unique_ptr<ICalculatable> current_;
//     std::unique_ptr<ICalculatable> left_;
//     std::unique_ptr<ICalculatable> right_;

//     Node(const Node & orig) = delete;
//     Node & operator = (Node && orig);
//     ~Node() = default;
// };

// class Tree
// {

// public:
//     Tree()
//     {};

//     Tree(std::unique_ptr<Node> root);
//     void Add(std::unique_ptr<Node> node);
//     Node& GetRoot();

// private:
//     std::unique_ptr<Node> root_;
// };


void parse_arguments(int argc, char** argv, std::vector<std::string>& vec);
double solve_expression(std::vector<std::string>& vec);
