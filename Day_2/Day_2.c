//
// Created by paula on 02/12/2024.
//
#include "../common/common.h"
#include "Day_2.h"

#include <stdbool.h>
#include <stdlib.h>

struct list_t {
    int* data;
    int size;
};
typedef struct list_t list;

list get_line(char* line_start) {
    char* line_end = line_start;
    int n_numbers = 1;
    while (*line_end != '\n') {
        if (*line_end == ' ') {
            n_numbers++;
        }
        line_end++;
    }
    int* numbers = (int*)malloc(n_numbers * sizeof(int));
    char* seeker = line_start;
    for (int i = 0; i < n_numbers; i++) {
        numbers[i] = (int)strtol(seeker, NULL, 10);
        next_number(&seeker);
    }
    list rt_lst = {numbers, n_numbers};
    return rt_lst;
}

bool is_safe(list line) {
    if (*(line.data) < *(line.data + 1)) {
        for (int i = 0; i < line.size-1; i++) {
            if (line.data[i+1]-line.data[i] > 3 || line.data[i+1]-line.data[i] < 1) {
                return false;
            }
        }
        return true;
    } else if (*(line.data) == *(line.data + 1)) {
        return false;
    } else {
        for (int i = 0; i < line.size-1; i++) {
            if (line.data[i]-line.data[i+1] > 3 || line.data[i]-line.data[i+1] < 1) {
                return false;
            }
        }
        return true;
    }
}

bool is_safe_pt2(list line) {
    if (is_safe(line))
        return true;
    list new_lst;
    new_lst.size = line.size - 1;
    for (int i = 0; i < line.size; i++) {
        new_lst.data = (int*)malloc(new_lst.size * sizeof(int));
        remove_element(line.data, new_lst.data, line.size, new_lst.size, i);
        if (is_safe(new_lst)) {
            free(new_lst.data);
            return true;
        }
        free(new_lst.data);
    }
    return false;

}


int day_2(char* input, int result[2]) {
    const int n_lines = count_char(input, '\n');
    char* current_line = input;
    int n_safe_pt1 = 0;
    int n_safe_pt2 = 0;
    for (int i = 0; i < n_lines; i++) {
        list line = get_line(current_line);
        next_line(&current_line);
        n_safe_pt1 += is_safe(line);
        n_safe_pt2 += is_safe_pt2(line);
        free(line.data);
    }
    result[0] = n_safe_pt1;
    result[1] = n_safe_pt2;
    return 0;
}

