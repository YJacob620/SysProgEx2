#include <stdio.h>
#include <stdlib.h>

#define SACK_WEIGHT 20
#define ITEM_NUM 5
#define DEFAULT_NAME_LENGTH 20

typedef struct item { // honestly struct not truly needed here, mainly for practice
    char* name;
    int value;
    int weight;
} Item;

Item* createItems() {
    Item* items = malloc(ITEM_NUM * sizeof(Item)); // use malloc so array won't "disappear" when exiting scope 

    for (int i = 0; i < ITEM_NUM; i++) {
        char* curr_name = (char*)malloc(DEFAULT_NAME_LENGTH); // might want to allocate more memory for name
        char letter = ' ';
        int name_len = DEFAULT_NAME_LENGTH, j = 0;
        while (letter == ' ') {
            scanf("%c", &letter);
        }
        while (letter != ' ') { // loop until done scanning name
            if (j + 1 >= name_len) { // handles cases of long names (longer than 20 characters)
                name_len *= 2;
                curr_name = (char*)realloc(curr_name, name_len); // allocate more memory for name
            }
            curr_name[j++] = letter;
            scanf("%c", &letter);
        }
        curr_name[j] = '\0';
        items[i].name = curr_name;

        int v, w;
        scanf("%d", &v); // enter value of item
        scanf("%d", &w); // enter weight of item
        items[i].value = v;
        items[i].weight = w;
    }
    return items;
}

int knapSack(int weights[], int values[], int selected_bool[]) {
    int DP_arr[ITEM_NUM + 1][SACK_WEIGHT + 1]; // the i-th row signifies being exposed to the first i items

    for (int i = 0;i <= ITEM_NUM;i++) { // base case for 0 weight limit
        DP_arr[i][0] = 0;
    }
    for (int i = 0;i <= SACK_WEIGHT;i++) { // base case for 0 exposed items
        DP_arr[0][i] = 0;
    }
    for (int i = 1;i <= ITEM_NUM;i++) {
        for (int j = 1;j <= SACK_WEIGHT;j++) {
            int a = DP_arr[i - 1][j]; // case if didn't choose to bag the i-th item
            int b = 0;
            if (j - (int)weights[i - 1] >= 0) {
                b = DP_arr[i - 1][j - (int)weights[i - 1]] + values[i - 1]; // case if chose to bag the i-th item
            }
            DP_arr[i][j] = a > b ? a : b;
        }
    }
    int i = ITEM_NUM, j = SACK_WEIGHT;
    int ans = DP_arr[i][j];

    while (i > 0) { // backtracing from the bottom-right corner of the matrix to find which items were added
        if (DP_arr[i][j] > DP_arr[i - 1][j]) {
            selected_bool[i - 1] = 1;
            j -= (int)weights[i - 1];
            i--;
        }
        else {
            i--;
        }
    }
    return ans;
}

int main() {
    Item* items = createItems();
    int values[ITEM_NUM], weights[ITEM_NUM];
    for (int i = 0; i < ITEM_NUM; i++) {
        values[i] = items[i].value;
        weights[i] = items[i].weight;
    }

    int selected_bool[ITEM_NUM];
    for (int i = 0; i < ITEM_NUM; i++) { // by default no item is selected 
        selected_bool[i] = 0;
    }

    int ans = knapSack(weights, values, selected_bool);
    printf("Maximum profit: %d\n", ans);
    printf("Selected items:");
    for (int i = 0; i < ITEM_NUM; i++) {
        if (selected_bool[i] == 1) {
            Item curr_item = items[i];
            printf(" %s", curr_item.name);
        }
    }
    // printf("\n"); // given tests only work without this line
    free(items);
    return 0;
}
