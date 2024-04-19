#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 1000

int minimum(int a, int b, int c) {
    int min_val = a;
    if (b < min_val)
        min_val = b;
    if (c < min_val)
        min_val = c;
    return min_val;
}

int calculate_distance(const char *str1, const char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    int i, j;
    int **matrix = (int **)malloc((len1 + 1) * sizeof(int *));
    for (i = 0; i <= len1; i++) {
        matrix[i] = (int *)malloc((len2 + 1) * sizeof(int));
    }

    for (i = 0; i <= len1; i++)
        matrix[i][0] = i;

    for (j = 0; j <= len2; j++)
        matrix[0][j] = j;

    for (i = 1; i <= len1; i++) {
        for (j = 1; j <= len2; j++) {
            int cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
            matrix[i][j] = minimum(matrix[i - 1][j] + 1,
                                   matrix[i][j - 1] + 1,
                                   matrix[i - 1][j - 1] + cost);
        }
    }

    int distance = matrix[len1][len2];

    for (i = 0; i <= len1; i++) {
        free(matrix[i]);
    }
    free(matrix);

    return distance;
}

int main() {
    FILE *file_ptr = fopen("input.txt", "r");
    if (file_ptr == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return 1;
    }

    char str1[MAX_LENGTH], str2[MAX_LENGTH];
    while (fscanf(file_ptr, "%s %s", str1, str2) == 2) {
        int distance = calculate_distance(str1, str2);
        printf("Levenshtein distance between '%s' and '%s' is: %d\n", str1, str2, distance);
    }

    fclose(file_ptr);
    return 0;
}
