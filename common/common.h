//
// Created by paula on 02/12/2024.
//

#ifndef COMMON_H
#define COMMON_H
void checkError(int err, const char* msg);
char* get_input(const char* path);
int count_char(const char* str, char c);
void next_number(char** str);
void sortl(long* arr, int len);
int countl(long* arr, int len, long num);
#endif //COMMON_H
