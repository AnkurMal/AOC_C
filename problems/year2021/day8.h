#include <stdio.h>

#include "utilities/string.h"

void part_1() {
    String data = string_read_file("data/year2021/day8.txt");
    StringSplit lines = string_lines(&data);
    int counter = 0;

    foreach (line, lines) {
        StringSplit spl = string_split(line, " ");
        for (size_t i = 11; i < spl.len; i++) {
            size_t len = split_at(&spl, i).len;
            if (len == 2 || len == 4 || len == 3 || len == 7) counter++;
        }
        split_free(&spl);
    }

    split_free(&lines);
    string_free(&data);

    printf("Part 1: %d", counter);
}

bool contains_one(String* str, String* one_pattern) {
    return (string_contains(str, one_pattern->arr[0]) &&
            string_contains(str, one_pattern->arr[1]));
}

bool contains_four(String* str, String* four_pattern) {
    foreach (i, *four_pattern) {
        if (!string_contains(str, *i)) return false;
    }
    return true;
}

bool is_five(String* str, String* six_pattern) {
    foreach (i, *str) {
        if (!string_contains(six_pattern, *i)) return false;
    }
    return true;
}

void part_2() {
    String data = string_read_file("data/year2021/day8.txt");
    StringSplit lines = string_lines(&data);
    int sum = 0;

    foreach (line, lines) {
        StringSplit spl = string_split(line, " ");
        String one_pattern, six_pattern, four_pattern;
        int digit = 0;

        for (int i = 0; i < 10; i++) {
            String st = split_at(&spl, i);
            if (st.len == 2)
                one_pattern = st;
            else if (st.len == 4)
                four_pattern = st;
        }

        for (int i = 0; i < 10; i++) {
            String st = split_at(&spl, i);
            if (st.len == 6 && !contains_one(&st, &one_pattern)) {
                six_pattern = st;
                break;
            }
        }

        for (size_t i = 11; i < spl.len; i++) {
            String curr = split_at(&spl, i);
            size_t len = curr.len;
            if (len == 2)
                digit = digit * 10 + 1;
            else if (len == 3)
                digit = digit * 10 + 7;
            else if (len == 4)
                digit = digit * 10 + 4;
            else if (len == 7)
                digit = digit * 10 + 8;
            else if (len == 5) {
                if (contains_one(&curr, &one_pattern))
                    digit = digit * 10 + 3;
                else if (is_five(&curr, &six_pattern))
                    digit = digit * 10 + 5;
                else
                    digit = digit * 10 + 2;
            } else if (len == 6) {
                if (!contains_one(&curr, &one_pattern))
                    digit = digit * 10 + 6;
                else if (contains_four(&curr, &four_pattern))
                    digit = digit * 10 + 9;
                else
                    digit = digit * 10 + 0;
            }
        }

        sum += digit;
        split_free(&spl);
    }

    printf("Part 2: %d", sum);
    split_free(&lines);
    string_free(&data);
}