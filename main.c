#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "common/common.h"
#include "Day_1/Day_1.h"
#include "Day_2/Day_2.h"
#include "Day_3/Day_3.h"

#define DAY_MAX 1

typedef int (*func_ptr_t)(char*, int[2]);

void run_day(int num_day, func_ptr_t day_func) {
    long result[2];
    char str[1024];
    sprintf(str, "../Day_%d/input.txt", num_day);
    char* file_day = get_input(str);
    int err = day_func(file_day, result);
    sprintf(str, "Error in day %d", num_day);
    checkError(err, str);
    free(file_day);
    sprintf(str, "Day %d:\n\tPart1: %d\t Part2: %d\n", num_day, result[0], result[1]);
    printf("%s\n", str);
}

int main(void) {
    run_day(1, day_1);
    run_day(2, day_2);
    run_day(3, day_3);
    return 0;
}
