#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(int argc, const char *argv[]) {
    char *s = (char *)malloc(sizeof(char) * 128);
    free(s);
    strcpy(s, "Hello world!");
    printf("string is: %s\n", s);
    return 0; 
}