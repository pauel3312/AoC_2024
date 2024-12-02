#include <stdio.h>
#include <stdlib.h>
#include <direct.h>

#include "Day_1/Day_1.h"


char* get_input(const char* path) {
    char* buffer = NULL;
    FILE * f = fopen (path, "r");
    printf("%p\n", f);

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

int main(void) {
    char* file_day_1 = get_input("../Day_1/input.txt");
    printf("Day 1: %d\n", day_1(file_day_1));
    free(file_day_1);
    return 0;
}