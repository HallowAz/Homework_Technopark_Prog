#include <iostream>
#include "utils.hpp"




int main(int argc, char** argv)
{
    std::vector<std::string> parse_vec;
    //std::vector<std::unique_ptr<ICalculatable>> vec_of_nodes;
    parse_arguments(argc, argv, parse_vec);


    // std::unique_ptr<ICalculatable> left = std::make_unique<Number>((std::stod(parse_vec[0])));
    // std::unique_ptr<ICalculatable> right = std::make_unique<Number>((std::stod(parse_vec[2])));
    
    // std::unique_ptr<ICalculatable> plus = std::make_unique<Minus>(std::move(left), std::move(right));
    std::cout << solve_expression(parse_vec);
    //std::cout << std::size(vec_of_nodes) << std::endl; 
    return 0;
}
