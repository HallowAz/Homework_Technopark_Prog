#include <iostream>
#include <string>
#include <fstream>

#include "utils.hpp"

// Задание: Вывести число мужчин и женщин исполнителей, живших в год, который передан в аргументах командной строки

int main(int argc, char *argv[])
{
    std::string artist_filename{"../static/"}; // Получение названий необходимых файлов (файлов gender и artist)
    artist_filename += argv[1];

    std::string gender_filename{"../static/"}; 
    gender_filename += argv[2];

    int year = std::stoi(argv[3]); // Инициализация года из условия задачи

    print_for_task(artist_filename, gender_filename, year);

    return 0;
}