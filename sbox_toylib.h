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

    float sandboxed_cmult(int x, float y);
    int sandboxed_cgetstrlen(char *s);
    void sandboxed_cstrconcat(char *s1, char *s2, char *res);
    // ToyOutClass* sandboxed_cgetclass(ToyInClass *c);
    void sandboxed_cgetclass(ToyInClass *c, ToyOutClass *res);

    // ToyOutList* sandboxed_cgetlist(ToyInList *l);
    void sandboxed_crevlist(int* inList, int* outList, int size);

#ifdef __cplusplus
}
#endif
