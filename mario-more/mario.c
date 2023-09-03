#include <stdio.h>

int main() {
    int h;

    while (1) {
        printf("Height: ");
        if (scanf("%d", &h) != 1 || !(h > 0 && h <= 8)) {
            while (getchar() != '\n'); // Clear input buffer
        } else {
            break;
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < h + i + 3; j++) {
            if (j == h || j == h + 1 || j + i < h - 1) {
                printf(" ");
            } else {
                printf("#");
            }
        }
        printf("\n");
    }

    return 0;
}