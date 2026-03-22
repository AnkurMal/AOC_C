#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "utilities/string.h"

int get_answer(bool is_part_2) {
    String data = string_read_file("data/year2021/day7.txt");
    StringSplit spl = string_split(&data, ",");
    long* arr = malloc(spl.len * sizeof(long));
    int sum = INT_MAX;

    foreach_enumerate(i, ind, spl) arr[ind] = string_parse(i, long);
    for (size_t i = 0; i < spl.len; i++) {
        int int_sum = 0;

        for (size_t j = 0; j < spl.len; j++) {
            if (!is_part_2)
                int_sum += abs(arr[j] - arr[i]);
            else {
                int sub = abs(arr[j] - (int)i);
                int_sum += (sub * (sub + 1)) / 2;
            }
        }

        sum = min(sum, int_sum);
    }

    free(arr);
    split_free(&spl);
    string_free(&data);

    return sum;
}

void part_1() { printf("Part 1: %d", get_answer(false)); }

void part_2() { printf("Part 2: %d", get_answer(true)); }