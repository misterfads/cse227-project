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
    void c_getclass(struct ToyInClass *c, struct ToyOutClass *res);
    // struct ToyOutList *c_getlist(struct ToyInList *l);
    void c_revlist(int* inList, int *outList, int size);

#ifdef __cplusplus
}
#endif
