#pragma once
#include <string>

struct Person
{
    char gender = 'n';
    int date_of_birth = 0;
    int date_of_death = 0;
};

void get_genders(const std::string &gender_file_line, char &male_gender_id, char &female_gender_id); 
void work_with_gender_file(const std::string &gender_filename, char &male_gender_id, char &female_gender_id);
int work_with_artist_file(const std::string &artist_filename, const char male_gender_id, const char female_gender_id, const int year);
std::string get_artist(const std::string &file_line, const char male_gender_id, const char female_gender_id, const int year);
void print_for_task(const std::string &artist_filename, const std::string &gender_filename, const int year);
void set_person_values(const int count_of_tab, Person &artist, const std::string &file_line, const char male_gender_id,
                       const char female_gender_id, const int current_j);
bool is_number_func(const std::string check_str);
