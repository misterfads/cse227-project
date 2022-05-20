#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct ToyInClass {
    int x;
    float y;
};

struct ToyOutClass {
    float w;
    int z;
};

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


struct ToyOutClass *c_getclass(struct ToyInClass *c) {
    struct ToyOutClass *res = malloc(sizeof(struct ToyOutClass));
    res->w = (c->y)*1.5;
    res->z = c->x + 5;
    return res;
}
