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

void next_number(char** str) {
    while (isdigit(**str)) {
        (*str)++;
    }
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

int countl(long* arr, int len, long num) {
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
    FILE * f = fopen (path, "r");

    if (f)
    {
        fseek (f, 0, SEEK_END);
        const long length = ftell(f);
        fseek (f, 0, SEEK_SET);
        buffer = malloc(length);
        if (buffer)
        {
            fread (buffer, 1, length, f);
        }
        fclose (f);
    }
    return buffer;
}

int count_char(const char *str, char c) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == c) {
            count++;
        }
    }
    return count;
}
