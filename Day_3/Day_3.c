//
// Created by paula on 03/12/2024.
//

#include "Day_3.h"

#include <stdbool.h>
#include <stdlib.h>

#include "../common/common.h"

int check_mul(char* start) {
    if (start[0] != 'm' || start[1] != 'u' || start[2] != 'l' || start[3] != '(') {
        return 0;
    }
    start += 4;
    int operand_1 = strtol(start, NULL, 10);
    skip_number(&start);
    if (*start != ',') {
        return 0;
    }
    start++;
    int operand_2 = strtol(start, NULL, 10);
    skip_number(&start);
    if (*start != ')') {
        return 0;
    }
    return operand_1 * operand_2;
}

int day_3(char* input, int result[2]) {
    int sum_part_1 = 0;
    int sum_part_2 = 0;
    bool mul_enable = true;
    for (char* p = input; *p != '\0'; p++) {
        if (*p == 'm') {
            sum_part_1 += check_mul(p);
            if (mul_enable) {
                sum_part_2 += check_mul(p);
            }
        } else if (*p == 'd') {
            if (*(p+1) == 'o') {
                if (*(p+2) == 'n'&&*(p+3) == '\''&&*(p+4) == 't'&&*(p+5) == '('&&*(p+6) == ')') {
                    mul_enable = false;
                } else if (*(p+2) == '('&&*(p+3)==')') {
                    mul_enable = true;
                }
            }
        }
    }
    result[0] = sum_part_1;
    result[1] = sum_part_2;
    return 0;
}

