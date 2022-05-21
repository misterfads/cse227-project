#pragma once



#ifdef __cplusplus
extern "C" {
#endif
    struct ToyInClass {
        int x;
        float y;
    };
    struct ToyOutClass {
        float w;
        int z;
    };

    struct ToyInList {
        int x;
        float y;
    };
    struct ToyOutList {
        float w;
        int z;
    };

    float sandboxed_cmult(int x, float y);
    int sandboxed_cgetstrlen(char *s);
    void sandboxed_cstrconcat(char *s1, char *s2, char *res);
    ToyOutClass* sandboxed_cgetclass(ToyInClass *c);

    ToyOutList* sandboxed_cgetlist(ToyInList *l);
#ifdef __cplusplus
}
#endif
