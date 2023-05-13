#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(void) {
    char *s = malloc(sizeof(char));
    strcpy(s, "Hello world!");
    printf("string is: %s\n", s);
    free(s);
    return 0;
}