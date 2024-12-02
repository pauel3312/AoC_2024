//
// Created by paula on 02/12/2024.
//

#include "Day_1.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "../common/common.h"


int day_1(char* input, long output[2]) {
    const int n_lines = count_char(input, '\n');
    long* list_1 = malloc(sizeof(long) * n_lines);
    long* list_2 = malloc(sizeof(long) * n_lines);
    char* seeker = input;
    for (int i = 0; i < n_lines; i++) {
        list_1[i] = strtol(seeker, NULL, 10);
        next_number(&seeker);
        list_2[i] = strtol(seeker, NULL, 10);
        next_number(&seeker);
    }

    // Part 1 compute
    sortl(list_1, n_lines);
    sortl(list_2, n_lines);

    long sum_dist = 0;
    for (int i = 0; i < n_lines; i++) {
        sum_dist += abs(list_1[i] - list_2[i]);
    }

    //Part 2 compute
    long sim_score = 0;
    for (int i = 0; i < n_lines; i++) {
        sim_score += list_1[i]*countl(list_2, n_lines, list_1[i]);
    }

    output[0] = sum_dist; // Part 1 solution

    output[1] = sim_score;

    free(list_1);
    free(list_2);
    return 0;
}
