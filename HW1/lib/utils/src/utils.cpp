#include "utils.hpp"
#include <iostream>
#include <fstream>
#include <string>

// Функция отвечает за поиск пола в строке файла gender
void get_genders(const std::string &gender_file_line, char &male_gender_id, char &female_gender_id)
{
    for (size_t j = 0; j < std::size(gender_file_line); j++)
    {
        if (gender_file_line[j] == '\t' && gender_file_line.substr(j + 1, 4) == "Male")
        {
            male_gender_id = gender_file_line[j - 1];
            j = std::size(gender_file_line);
        }
        else if (gender_file_line[j] == '\t' && gender_file_line.substr(j + 1, 6) == "Female")
        {
            female_gender_id = gender_file_line[j - 1];
            j = std::size(gender_file_line);
        }
    }
}

// Функция отвечает за получение строки из файла gender
void work_with_gender_file(const std::string &gender_filename, char &male_gender_id, char &female_gender_id)
{
    std::string file_line;
    std::ifstream gender_file{gender_filename};

    if (!gender_file.is_open())
    {
        std::cout << "Error with opening gender file" << std::endl;
        male_gender_id = 'n';
        female_gender_id = 'n';
    }
    else
    {
        while (getline(gender_file, file_line))
            get_genders(file_line, male_gender_id, female_gender_id);
    }

    gender_file.close();
}

// Функция отвечает за получение нужного артиста из файла artist
std::string get_artist(const std::string &file_line, const char male_gender_id, const char female_gender_id, const int year)
{
    Person artist;
    int count_of_tab = 0;

    for (size_t j = 0; j < std::size(file_line); j++)
    {
        if (file_line[j] == '\t')
        {
            count_of_tab++;
            set_person_values(count_of_tab, artist, file_line, male_gender_id, female_gender_id, j);
        }
    }

    if (0 < artist.date_of_birth && artist.date_of_birth <= year && artist.date_of_death >= year && artist.gender != 'n')
        return file_line;

    return "None";
}

// Функция отвечает за проверку строки файла артистов на соответствие заданию
void set_person_values(const int count_of_tab, Person &artist, const std::string &file_line, const char male_gender_id,
                       const char female_gender_id, const int current_j)
{
    bool is_number = true;

    if (count_of_tab == 4)
    {
        is_number = is_number_func(file_line.substr(current_j + 1, 4));

        if (is_number)
            artist.date_of_birth = std::stoi(file_line.substr(current_j + 1, 4));
    }
    else if (count_of_tab == 7)
    {
        if (artist.date_of_birth != 0)
            artist.date_of_death = 3000;

        is_number = is_number_func(file_line.substr(current_j + 1, 4));

        if (is_number)
            artist.date_of_death = std::stoi(file_line.substr(current_j + 1, 4));
    }
    else if (count_of_tab == 12 && (file_line[current_j + 1] == male_gender_id || file_line[current_j + 1] == female_gender_id))
        artist.gender = file_line[current_j + 1];
}

// Функция проверяет является ли переданная строка числом в символьном виде
bool is_number_func(const std::string check_str)
{
    for (int i = 0; i < 4; i++)
    {
        if (!isdigit(check_str[i]))
            return false;
    }

    return true;
}

// Функция счиатет количество подхлодящих артистов
int work_with_artist_file(const std::string &artist_filename, const char male_gender_id, const char female_gender_id, const int year)
{
    std::ifstream artist_file{artist_filename};
    std::string file_line;
    std::string result_artist;
    int result_count = 0;

    if (!artist_file.is_open())
        std::cout << "Error with opening artist file" << std::endl;
    else
    {
        while (getline(artist_file, file_line))
        {
            result_artist = get_artist(file_line, male_gender_id, female_gender_id, year);
            if (result_artist != "None")
                result_count++;
        }
    }

    artist_file.close();

    return result_count;
}

// Функция выводит результат
void print_for_task(const std::string &artist_filename, const std::string &gender_filename, const int year)
{
    if (year < 0 || year > 2023)
        std::cout << "This year does not exist on today" << std::endl;
    else
    {
        char male_gender_id = 'n';
        char female_gender_id = 'n';

        work_with_gender_file(gender_filename, male_gender_id, female_gender_id);
        std::cout << "Number: " << work_with_artist_file(artist_filename, male_gender_id, female_gender_id, year) << std::endl;
    }
}
