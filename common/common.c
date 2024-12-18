//
// Created by paula on 02/12/2024.
//

#include "common.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void checkError(int err, const char* msg) {
    if (err) {
        printf("Error: %s\n", msg);
        exit(err);
    }
}

void skip_number(char** str) {
    while (isdigit(**str)) {
        (*str)++;
    }
}

int get_len_line(const char* line) {
    if (line == NULL) return -1;
    int cnt = 1;
    while (line[cnt-1] != '\n') { // Because a line is terminated by "\r\n", the condition needs to be on cnt-1
        cnt++;
    }
    return cnt;
}

bool find_in_str(char **str, char *c) {
    for (;**str!='\0'; *(str) += 1) {
        seek_to(str, *c);
        if (compare_strings_eo2(*str, c)) {
            return true;
        }
    }
    return false;
}

bool seek_to(char **str, char c) {
    for (;**str!='\0'; *(str) += 1) {
        if (**str == c) {
            return true;
        }
    }
    return false;
}


void next_number(char** str) {
    skip_number(str);
    while (!isdigit(**str)) {
        (*str)++;
    }

}

void sortl(long* arr, int len) {
    for (int i = 0; i < len-1;) {
        if (arr[i] <= arr[i + 1]) {
            i++;
        } else {
            long temp = arr[i];
            arr[i] = arr[i+1];
            arr[1 + i] = temp;
            if (i>0)
                i--;
        }
    }
}

int countl(const long* arr, const int len, const long num) {
    int count = 0;
    for (int i = 0; i < len; i++) {
        if (arr[i] == num) {
            count++;
        }
    }
    return count;
}

char* get_input(const char* path) {
    char* buffer = NULL;
    FILE* f = fopen(path, "rb");

    if (f)
    {
        fseek (f, 0, SEEK_END);
        const long length = ftell(f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc(length+1);
        if (buffer)
        {
            size_t bytes = fread (buffer, 1, length, f);
            buffer[bytes] = '\0';
        }
        fclose (f);
    }
    if (buffer == NULL) exit(1);
    return buffer;
}

int count_char(const char* str, char c) {
    if (str == NULL)
        return -1;
    int count = 0;
    for (const char* chr = str; *chr != '\0'; chr++) {
        if (*chr == c) {
            count++;
        }
    }
    return count;
}

int count_char_on_line(const char* str, char c) {
    if (str == NULL) return -1;
    int count = 0;
    for (const char* chr = str; *chr != '\n'; chr++) {
        if (*chr == c) {
            count++;
        }
    }
    return count;
}


void next_line(char** str) {
    while (**str != '\n') {
        if (**str == '\0') return;
        (*str)++;
    }
    (*str)++;
}

void remove_element(const int* in, int* out, int size_old, int size_new, int index) {
    if (in == NULL || out == NULL || index >= size_old || index < 0 || size_new+1 != size_old) {
        fprintf(stderr, "Error: Invalid parameters for remove_element\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < index; i++) {
        out[i] = in[i];
    }
    for (int i = index; i < size_new; i++) {
        out[i] = in[i + 1];
    }
}

bool compare_strings_eo2(const char* str1, const char* str2) {
    if (str1 == NULL || str2 == NULL) exit(1);
    for (int i = 0; str1[i] != '\0' && str2[i] != '\0'; i++) {
        if (str1[i] != str2[i]) return false;
    }
    return true;
}

