#include <iostream>
#include "utils.hpp"

int main(int argc, char** argv)
{
    std::vector<std::string> parse_vec;

    parse_arguments(argc, argv, parse_vec);

    if (parse_vec.empty())
        std::cout << "Empty expression" << std::endl;
    else
        std::cout << solve_expression(parse_vec) << std::endl;

    return 0;
}
