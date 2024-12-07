//
// Created by paula on 06/12/2024.
//

#include "Day_5.h"

#include <stdlib.h>

#include "../common/common.h"

struct rulesFor {
    int before;
    int n_afters;
    int next_after;
    int* afters;
};
typedef struct rulesFor rulesFor_t;


int get_rule_index(const rulesFor_t* rules, int n_defined_rules, int value) {
    for (int i = 0; i < n_defined_rules; i++) {
        if (rules[i].before == value) {
            return i;
        }
    }
    return -1;
}

int day_5(char* input, int result[2]) {
    char* pages_update_section = input;
    bool has_section_sep = find_in_str(&pages_update_section, "\r\n\r\n");
    if (!has_section_sep) {return -1;}
    pages_update_section += 4;
    int n_rules = count_char(input, '\n')-(count_char(pages_update_section, '\n')+2);
    char* seeker = input;
    int n_defined_rules = 0;
    rulesFor_t rules[n_rules];
    for (int i = 0; i < n_rules; i++) {
        rules[i].next_after = 0;
        rules[i].n_afters = 0;
    }
    for (int i = 0; i < n_rules; i++) {
        int before = strtol(seeker, NULL, 10);
        int rule_index = get_rule_index(rules, n_defined_rules, before);
        if (rule_index == -1) {
            rules[n_defined_rules].before = before;
            rules[n_defined_rules].n_afters++;
            n_defined_rules++;
        } else {
            rules[rule_index].before = before;
            rules[rule_index].n_afters++;
        }
        next_line(&seeker);
    }
    for (int i = 0; i < n_defined_rules; i++) {
        rules[i].afters = malloc(sizeof(int) * rules[i].n_afters);
    }
    seeker = input;
    for (int i = 0; i < n_rules; i++) {
        int before = strtol(seeker, NULL, 10);
        find_in_str(&seeker, "|");
        seeker++;
        int after = strtol(seeker, NULL, 10);
        int rule_index = get_rule_index(rules, n_defined_rules, before);
        if (rule_index == -1) {return -1;}
        rules[rule_index].afters[rules[rule_index].next_after] = after;
        rules[rule_index].next_after++;
        next_line(&seeker);
    }
    for (int i = 0; i < n_defined_rules; i++) {
        free(rules[i].afters);
    }
    return 0;
}
