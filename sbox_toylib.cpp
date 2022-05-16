// ANCHOR: imports
// We're going to use RLBox in a single-threaded environment.
#define RLBOX_SINGLE_THREADED_INVOCATIONS
// All calls into the sandbox are resolved statically.
#define RLBOX_USE_STATIC_CALLS() rlbox_noop_sandbox_lookup_symbol

#include <stdio.h>
#include <cassert>
#include <rlbox/rlbox.hpp>
#include <rlbox/rlbox_noop_sandbox.hpp>

#include "toylib.h"
#include "sbox_toylib.h"

using namespace std;
using namespace rlbox;

// Define base type for mylib using the noop sandbox
RLBOX_DEFINE_BASE_TYPES_FOR(toylib, noop);

float sandboxed_cmult(int x, float y)
{
  // Declare and create a new sandbox
  rlbox_sandbox_toylib sandbox;
  sandbox.create_sandbox();

  // call the add function and check the result:
  // auto val = sandbox.invoke_sandbox_function(cmult, 3, 4.0);
  // printf("cmult 3*4.0 = %.3f\n", val);
  float result = sandbox.invoke_sandbox_function(c_mult, x, y)
                     .copy_and_verify([](float ret)
                                      {
      printf("Adding... 3+4 = %.3f\n", ret);
      return ret; });

  // destroy sandbox
  sandbox.destroy_sandbox();

  return result;
}

int sandboxed_cgetstrlen(char *s)
{
  rlbox_sandbox_toylib sandbox;
  sandbox.create_sandbox();
  size_t strSize = strlen(s) + 1;

  tainted_toylib<char *> taintedStr = sandbox.malloc_in_sandbox<char>(strSize);
  strncpy(taintedStr
              .unverified_safe_pointer_because(strSize, "writing to region"),
          s, strSize);

  int result = sandbox.invoke_sandbox_function(c_getstrlen, taintedStr)
                   .copy_and_verify([](int ret)
                                    {
      printf("Length of input string is %d\n", ret);
      return ret; });

  sandbox.destroy_sandbox();
  return result;
}

void sandboxed_cstrconcat(char *s1, char *s2, char *res)
{
  rlbox_sandbox_toylib sandbox;
  sandbox.create_sandbox();
  size_t s1Size = strlen(s1) + 1;
  size_t s2Size = strlen(s2) + 1;

  tainted_toylib<char *> taintedS1 = sandbox.malloc_in_sandbox<char>(s1Size + s2Size);
  tainted_toylib<char *> taintedS2 = sandbox.malloc_in_sandbox<char>(s2Size);
  strncpy(taintedS1
              .unverified_safe_pointer_because(s1Size, "writing to region"),
          s1, s1Size);
  strncpy(taintedS2
              .unverified_safe_pointer_because(s2Size, "writing to region"),
          s2, s2Size);

  auto result = sandbox.invoke_sandbox_function(c_strconcat, taintedS1, taintedS2)
                     .copy_and_verify_string([](unique_ptr<char []> ret)
                                      {
      
      return ret; });
  printf("Concatenated string is %s \n", result.get());
  sandbox.destroy_sandbox();
  int i= 0;
  while(result.get()[i] != '\0'){
    res[i] = result.get()[i];
    i++;
  }
}