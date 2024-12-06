//
// Created by paula on 05/12/2024.
//

#include "Day_4.h"

#include <ctype.h>
#include <stdlib.h>

#include "../common/common.h"

bool XMAS_horiz(const char* start) {
    if (start == NULL) {return -1;}
    return compare_strings_eo2(start, "XMAS") || compare_strings_eo2(start, "SAMX");
}

bool XMAS_vert(const char* start, int current_line, int n_lines, int len_line) {
    if (current_line > n_lines-4) return false;
    char to_cmp[] = "INIT";
    for (int i=0; i<4; i++) {
        to_cmp[i] = start[len_line*i];
    }
    return compare_strings_eo2("XMAS", to_cmp) || compare_strings_eo2("SAMX", to_cmp);
}

bool XMAS_diag_fwd(const char* start, int current_line, int n_lines, int len_line) {
    if (current_line > n_lines-4 || get_len_line(start) < 4) return false;
    char to_cmp[] = "INIT";
    for (int i=0; i<4; i++) {
        to_cmp[i] = start[len_line*i+i];
    }
    return compare_strings_eo2("XMAS", to_cmp) || compare_strings_eo2("SAMX", to_cmp);
}

bool XMAS_diag_bwd(const char* start, const char* line_start, int current_line, int n_lines, int len_line) {
    if (current_line > n_lines-4 || start-line_start < 3) return false;
    char to_cmp[] = "INIT";
    for (int i=0; i<4; i++) {
        to_cmp[i] = start[len_line*i-i];
    }
    return compare_strings_eo2("XMAS", to_cmp) || compare_strings_eo2("SAMX", to_cmp);
}

bool X_MAS(const char* start, int current_line, int n_lines, int len_line) {
    if (current_line > n_lines-3 || get_len_line(start) < 3) return false;
    char to_cmp_fwd[] = "INI", to_cmp_bwd[] = "INI";
    for (int i=0; i<3; i++) {
        to_cmp_fwd[i] = start[len_line*i+i];
        to_cmp_bwd[i] = start[len_line*i+(2-i)];
    }
    return (compare_strings_eo2(to_cmp_fwd, "MAS") || compare_strings_eo2(to_cmp_fwd, "SAM")) &&
        (compare_strings_eo2(to_cmp_bwd, "MAS") || compare_strings_eo2(to_cmp_bwd, "SAM"));
}

int day_4(char* input, int result[2]) {
    const int n_lines = count_char(input, '\n');
    const int len_line = get_len_line(input);
    if (len_line == -1) return -1;
    int result_p1 = 0;
    int result_p2 = 0;
    char* line_ptr = input;
    for (int current_line = 0; current_line < n_lines; current_line++) {
        for (char* current_ptr = line_ptr; *current_ptr != '\n'; current_ptr++) {
            result_p1 += XMAS_horiz(current_ptr);
            result_p1 += XMAS_vert(current_ptr, current_line, n_lines, len_line);
            result_p1 += XMAS_diag_fwd(current_ptr, current_line, n_lines, len_line);
            result_p1 += XMAS_diag_bwd(current_ptr, line_ptr, current_line, n_lines, len_line);
            result_p2 += X_MAS(current_ptr, current_line, n_lines, len_line);
        }
        next_line(&line_ptr);
    }
    result[0] = result_p1;
    result[1] = result_p2;
    return 0;
}
