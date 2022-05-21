// cmult.c
#pragma once

#ifdef __cplusplus
extern "C" {
#endif
    struct ToyOutClass;
    struct ToyInClass;

    struct ToyOutList;
    struct ToyInList;

    float c_mult(int int_param, float float_param);
    int c_getstrlen(char *s);
    char* c_strconcat(char *s1, char *s2);
    struct ToyOutClass *c_getclass(struct ToyInClass *c);
    struct ToyOutList *c_getlist(struct ToyInList *l);   

#ifdef __cplusplus
}
#endif
