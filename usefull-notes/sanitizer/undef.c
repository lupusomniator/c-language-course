#include <stdio.h>

int main() {
    /* Overflows an unsigned integer by shifting it 32 times */
    printf("%d", 1u >> 32);
}
