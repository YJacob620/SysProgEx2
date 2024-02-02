#include <stdio.h>
#include <stdlib.h>

typedef struct item {
    float weight;
    float value;
}Item;

Item* create5Items() {
    Item* items = malloc(5 * sizeof(Item)); // so it won't "disappear" when exiting scope 
    for (int i = 0; i < 5; i++) {
        float w, v;
        // printf("Enter weight of item %d\n", i + 1);
        scanf("%f", &w);
        // printf("Enter value of item %d\n", i + 1);
        scanf("%f", &v);
        items[i].weight = w;
        items[i].value = v;
    }
    return items;
}

void selectItems(float weights[], float values[], char* strings[], int numStrings) {
    float DP_arr[6][21]; // the i-th row signifies being exposed to the first i items

    for (int i = 0;i < 6;i++) { // base case for 0 weight limit
        DP_arr[i][0] = 0;
    }
    for (int i = 0;i < 21;i++) { // base case for 0 items
        DP_arr[0][i] = 0;
    }
    for (int i = 1;i < 6;i++) {
        for (int j = 1;j < 21;j++) {
            float a = DP_arr[i - 1][j]; // didn't choose to bag the i-th item
            float b = 0;
            if (j - (int)weights[i - 1] >= 0) {
                b = DP_arr[i - 1][j - (int)weights[i - 1]] + values[i - 1]; // chose to bag the i-th item
            }
            DP_arr[i][j] = a > b ? a : b;
        }
    }
    int i = 5, j = 20;
    printf("Maximum profit: %d\n", (int)DP_arr[i][j]);

    char bestItems[5];
    int k = 0;
    while (i > 0) {
        if (DP_arr[i][j] > DP_arr[i - 1][j]) {
            bestItems[k++] = *strings[i - 1];
            j -= (int)weights[i - 1];
            i--;
        }
        else {
            i--;
        }
    }
    if (k > 0) {
        int l = 0;
        printf("Items that give the maximum profit: [%c", bestItems[l++]);
        while (l < k) {
            printf(", %c", bestItems[l++]);
        }
        printf("]\n");
    }
}

int main() {
    Item* items = create5Items();
    float weights[5], values[5];
    for (int i = 0; i < 5; i++) {
        weights[i] = items[i].weight;
        values[i] = items[i].value;
    }
    char names[] = { 'A','B','C','D','E' };
    char* strings[] = { &names[0],&names[1],&names[2],&names[3],&names[4] };

    printf("Items = [A,B,C,D,E]\n");
    printf("Weights = [%d", (int)weights[0]);
    int l = 1;
    while (l < 5) {
        printf(", %d", (int)weights[l++]);
    }
    printf("]\n");
    printf("Values = [%d", (int)values[0]);
    l = 1;
    while (l < 5) {
        printf(", %d", (int)values[l++]);
    }
    printf("]\nW = 20\n");
    selectItems(weights, values, strings, 5);

    free(items);
    return 0;
}