#ifndef INCLUDE_GAURD

#define INCLUDE_GAURD 1
#include <stdio.h>
#include "my_mat.h"

#endif


int main() {
    char c = 'Z';
    while (c != 'D' && c != EOF) {
        scanf("%c", &c);
        if (c == ' ') {
            scanf("%c", &c);
        }
        if (c == 'A') {
            A();
        }
        else if (c == 'B') {
            int i, j;
            scanf("%d%d", &i, &j);
            B(i, j);
        }
        else if (c == 'C') {
            int i, j;
            scanf("%d%d", &i, &j);
            int ans = C(i, j);
            printf("%d\n", ans);
        }
    }
    return 0;
}