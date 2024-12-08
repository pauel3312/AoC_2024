//
// Created by paula on 06/12/2024.
//

#include "Day_5.h"

#include <stdio.h>
#include <stdlib.h>

#include "../common/common.h"

struct rulesFor {
    int before;
    int n_afters;
    int next_after;
    int* afters;
};
typedef struct rulesFor rulesFor_t;


bool  checkUpdates_p1(char* line_start, const rulesFor_t* rules, int n_rules) {
    int n_pages = count_char_on_line(line_start, ',')+1;
    char* seeker = line_start;
    int* page_numbers = malloc(sizeof(int)*n_pages);
    page_numbers[0] = strtol(seeker, NULL, 10);
    for(int i = 1; i < n_pages; i++) {
        int err = !seek_to(&seeker, ',');
        if(err) {
            exit(1);
        }
        seeker++;
        page_numbers[i] = strtol(seeker, NULL, 10);
        rulesFor_t current_rule = {-1, -1, -1, NULL};
        for(int r = 0; r < n_rules; r++) {
            if (rules[r].before == page_numbers[i]) {
                current_rule = rules[r];
                break;
            }
        }
        if (current_rule.afters == NULL) {
            continue;
        }
        for (int j = 0; j<i; j++) {
            for (int k = 0; k<current_rule.n_afters; k++) {
                if (current_rule.afters[k] == page_numbers[j]) {
                    free(page_numbers);
                    return false;
                };
            }
        }
    }
    free(page_numbers);
    return true;
}

int get_middle_number(char* line_start) {
    int n_numbers = count_char_on_line(line_start, ',')+1;
    for(int i = 0; i < n_numbers/2; i++) {
        seek_to(&line_start, ',');
        line_start++;
    }
    return strtol(line_start, NULL, 10);
}


int get_rule_index(const rulesFor_t* rules, int n_defined_rules, int value) {
    for (int i = 0; i < n_defined_rules; i++) {
        if (rules[i].before == value) {
            return i;
        }
    }
    return -1;
}

void swap(int* arr, const int ia, const int ib) {
    int temp = arr[ia];
    arr[ia] = arr[ib];
    arr[ib] = temp;
}


int fix_and_get_middle(char* line_start, rulesFor_t* rules, int n_rules) {
    int n_pages = count_char_on_line(line_start, ',')+1;
    char* seeker = line_start;
    int* page_numbers = malloc(sizeof(int)*n_pages);
    page_numbers[0] = strtol(seeker, NULL, 10);
    for(int i = 1; i < n_pages; i++) {
        int err = !seek_to(&seeker, ',');
        if(err) {
            exit(1);
        }
        seeker++;
        page_numbers[i] = strtol(seeker, NULL, 10);
    }
    for (int i = 0; i < n_pages; i++) {
        rulesFor_t current_rule = {-1, -1, -1, NULL};
        for(int r = 0; r < n_rules; r++) {
            if (rules[r].before == page_numbers[i]) {
                current_rule = rules[r];
                break;
            }
        }
        if (current_rule.afters == NULL) {
            continue;
        }

        for (int j = 0; j<i; j++) {
            for (int k = 0; k<current_rule.n_afters; k++) {
                if (current_rule.afters[k] == page_numbers[j]) {
                    swap(page_numbers, i, j);
                    i=j-1;
                    break;
                }
            }
        }
    }
    const int rt = page_numbers[n_pages/2];
    free(page_numbers);
    return rt;
}


int day_5(char* input, int result[2]) {
    char* pages_update_section = input;
    bool has_section_sep = find_in_str(&pages_update_section, "\r\n\r\n");
    if (!has_section_sep) {return -1;}
    pages_update_section += 4;
    int n_rules = count_char(input, '\n')-(count_char(pages_update_section, '\n')+1);
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

    int n_good_updates = 0;
    int n_bad_updates = 0;
    char** good_updates_pointers = malloc(sizeof(char*) * count_char(pages_update_section, '\n'));
    char** bad_updates_pointers = malloc(sizeof(char*) * count_char(pages_update_section, '\n'));
    for (char* line_start = pages_update_section; *line_start != '\0'; next_line(&line_start)) {
        good_updates_pointers[n_good_updates] = line_start;
        bad_updates_pointers[n_bad_updates] = line_start;
        const bool is_good = checkUpdates_p1(line_start, rules, n_rules);
        n_good_updates += is_good;
        n_bad_updates += !is_good;
    }

    int p1_total = 0;
    int p2_total = 0;
    for(int i = 0; i < n_good_updates; i++) {
        p1_total += get_middle_number(good_updates_pointers[i]);
    }
    for (int i = 0; i < n_bad_updates; i++) {
        p2_total += fix_and_get_middle(bad_updates_pointers[i], rules, n_rules);
    }

    for (int i = 0; i < n_defined_rules; i++) {
        free(rules[i].afters);
    }
    free(good_updates_pointers);
    free(bad_updates_pointers);
    result[0] = p1_total;
    result[1] = p2_total;

    return 0;
}
