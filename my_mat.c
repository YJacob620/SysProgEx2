#ifndef INCLUDE_GAURD

#define INCLUDE_GAURD 1
#include <stdio.h>
#include "my_mat.h"

#endif


static int mat[10][10], FW_mat[10][10], did_mat = 0, did_FW = 0; // FW = Floyd-Warshall
static int infinity = 2147483647;

void A() {
    for (int i = 0;i < 10;i++) {
        for (int j = 0;j < 10;j++) {
            int val;
            scanf("%d", &val);
            mat[i][j] = val;
        }
    }
    did_mat = 1;
    did_FW = 0;
}

void do_FW() {
    for (int i = 0;i < 10;i++) { // FW_mat initialization
        for (int j = 0;j < 10;j++) {
            int val = mat[i][j];
            if (val == 0) {     // if there is no edge between 2 vertices
                val = infinity; // set distance between them to "infinity"
            }
            FW_mat[i][j] = val;
        }
    }
    for (int k = 0;k < 10;k++) { // the "meat" of the algorithm
        for (int i = 0;i < 10;i++) {
            for (int j = 0;j < 10;j++) {
                if (FW_mat[i][k] != infinity && FW_mat[k][j] != infinity) {
                    int new_path_weight = FW_mat[i][k] + FW_mat[k][j];
                    if (FW_mat[i][j] > new_path_weight) {
                        if (i != j) { // for some reason only mathces given outputs with this condition
                            FW_mat[i][j] = new_path_weight;
                        }
                    }
                }
            }
        }
    }
    did_FW = 1;
}

int C(int i, int j) {
    if (did_FW == 0) {
        if (did_mat == 0) {
            printf("Error: Matrix not initialized.\n");
            return -2;
        }
        do_FW();
    }
    int ans = FW_mat[i][j];
    if (ans == infinity) {
        ans = -1;
    }
    return ans;
}

void B(int i, int j) {
    if (did_mat == 0) {
        printf("Error: Matrix not initialized.\n");
        return;
    }
    int c_result = C(i, j);
    if (c_result == -1) {
        printf("False\n");
    }
    else {
        printf("True\n");
    }
}
