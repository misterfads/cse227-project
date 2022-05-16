#pragma once

#ifdef __cplusplus
extern "C" {
#endif
    float sandboxed_cmult(int x, float y);
    int sandboxed_cgetstrlen(char *s);
    void sandboxed_cstrconcat(char *s1, char *s2, char *res);
#ifdef __cplusplus
}
#endif
