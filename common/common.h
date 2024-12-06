//
// Created by paula on 02/12/2024.
//

#ifndef COMMON_H
#define COMMON_H
#include <stdbool.h>

void checkError(int err, const char* msg);
char* get_input(const char* path);
int count_char(const char* str, char c);
void next_number(char** str);
void skip_number(char** str);
void sortl(long* arr, int len);
int countl(const long* arr, int len, long num);
void next_line(char** str);
void remove_element(const int* in, int* out, int size_old, int size_new, int index);
int get_len_line(const char* line);
bool compare_strings_eo2(const char* str1, const char* str2);
#endif //COMMON_H
