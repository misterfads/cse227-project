#include <stdio.h>
#include <string.h>
// cmult.c
float c_mult(int int_param, float float_param) {
    float return_value = int_param * float_param;
    printf("    In cmult : int: %d float %.1f returning  %.1f\n", int_param,
            float_param, return_value);
    return return_value;
}


int c_getstrlen(char *s) {
    // char ss[] = "hello";
    // printf("Strlen is: %d\n", strlen(ss));
    return strlen(s);
}

char* c_strconcat(char *s1, char *s2) {
    strcat(s1, s2);
    return s1;
}