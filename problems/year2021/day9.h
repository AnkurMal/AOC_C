#include <stdio.h>
#include <stdlib.h>

#include "utilities/string.h"

typedef struct Array {
    long** data;
    size_t row, col;
} Array;

Array get_matrix() {
    String data = string_read_file("data/year2021/day9.txt");
    StringSplit lines = string_lines(&data);
    long** arr = malloc(lines.len * sizeof(long*));
    Array array;
    array.data = arr;
    array.row = lines.len;

    foreach_enumerate(line, ind, lines) {
        StringSplit spl = string_split(line, "");
        array.col = spl.len - 2;
        long* in = malloc((spl.len - 2) * sizeof(long));

        for (int i = 1; i < spl.len - 1; i++) {
            String st = split_at(&spl, i);
            in[i - 1] = string_parse(&st, long);
        }

        split_free(&spl);
        arr[ind] = in;
    }

    split_free(&lines);
    string_free(&data);

    return array;
}

void part_1() {
    Array arr = get_matrix();
    int sum = 0;

    for (int i = 0; i < arr.row; i++) {
        for (int j = 0; j < arr.col; j++) {
            long curr = arr.data[i][j];
            int is_low = 1;

            if (i - 1 >= 0 && arr.data[i - 1][j] <= curr) is_low = 0;
            if (i + 1 < arr.row && arr.data[i + 1][j] <= curr) is_low = 0;
            if (j - 1 >= 0 && arr.data[i][j - 1] <= curr) is_low = 0;
            if (j + 1 < arr.col && arr.data[i][j + 1] <= curr) is_low = 0;

            if (is_low) sum += curr + 1;
        }
    }

    printf("Part 1: %d", sum);
}

int is_low_point(Array* arr, int i, int j) {
    long curr = arr->data[i][j];
    if (i > 0 && arr->data[i - 1][j] <= curr) return 0;
    if (i < arr->row - 1 && arr->data[i + 1][j] <= curr) return 0;
    if (j > 0 && arr->data[i][j - 1] <= curr) return 0;
    if (j < arr->col - 1 && arr->data[i][j + 1] <= curr) return 0;
    return 1;
}

int dfs(Array* arr, int i, int j, int** visited) {
    if (i < 0 || j < 0 || i >= arr->row || j >= arr->col) return 0;
    if (visited[i][j]) return 0;
    if (arr->data[i][j] == 9) return 0;
    visited[i][j] = 1;

    return 1 + dfs(arr, i - 1, j, visited) + dfs(arr, i + 1, j, visited) +
           dfs(arr, i, j - 1, visited) + dfs(arr, i, j + 1, visited);
}

void part_2() {
    Array arr = get_matrix();
    int** visited = malloc(arr.row * sizeof(int*));
    for (size_t i = 0; i < arr.row; i++)
        visited[i] = calloc(arr.col, sizeof(int));
    int* basins = malloc(arr.row * arr.col * sizeof(int));
    int bcount = 0;
    for (int i = 0; i < arr.row; i++)
        for (int j = 0; j < arr.col; j++)
            if (is_low_point(&arr, i, j))
                basins[bcount++] = dfs(&arr, i, j, visited);
    for (int i = 0; i < bcount - 1; i++)
        for (int j = i + 1; j < bcount; j++)
            if (basins[i] < basins[j]) {
                int t = basins[i];
                basins[i] = basins[j];
                basins[j] = t;
            }

    printf("Part 2: %d", basins[0] * basins[1] * basins[2]);
}