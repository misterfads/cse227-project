// cmult.c
#pragma once

#ifdef __cplusplus
extern "C" {
#endif
    struct ToyOutClass;
    struct ToyInClass;

    float c_mult(int int_param, float float_param);
    int c_getstrlen(char *s);
    char* c_strconcat(char *s1, char *s2);
    struct ToyOutClass *c_getclass(struct ToyInClass *c);

#ifdef __cplusplus
}
#endif
