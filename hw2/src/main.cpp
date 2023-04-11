#include <iostream>
#include "utils.hpp"

int main(int argc, char** argv)
{
    std::vector<std::string> parse_vec;

    parse_arguments(argc, argv, parse_vec);

    // for (int i = 0; i < std::size(parse_vec); i++)
    // {
    //     std::cout << parse_vec[i] << std::endl;
    // }

    if (parse_vec.empty())
        std::cout << "Empty expression" << std::endl;
    else
        std::cout << solve_expression(parse_vec) << std::endl;
        
    return 0;
}
