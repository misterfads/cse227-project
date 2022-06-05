// ANCHOR: imports
// We're going to use RLBox in a single-threaded environment.
#define RLBOX_SINGLE_THREADED_INVOCATIONS
// All calls into the sandbox are resolved statically.
#define RLBOX_USE_STATIC_CALLS() rlbox_wasm2c_sandbox_lookup_symbol

#include <stdio.h>
#include <cassert>
#include <rlbox/rlbox.hpp>

#include "toylib.h"
#include "toylibwasm.h"
#include "sbox_toylib.h"
#include "rlbox_wasm2c_sandbox.hpp"

using namespace std;
using namespace rlbox;


// Define base type for mylib using the noop sandbox
RLBOX_DEFINE_BASE_TYPES_FOR(toylib, wasm2c);

float sandboxed_cmult(int x, float y)
{
  // Declare and create a new wasm sandbox
  rlbox_sandbox<rlbox_wasm2c_sandbox> sandbox;
  sandbox.create_sandbox("wasmsandbox");

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
  // Declare and create a new wasm sandbox
  rlbox_sandbox<rlbox_wasm2c_sandbox> sandbox;
  sandbox.create_sandbox("wasmsandbox");
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
  // Declare and create a new wasm sandbox
  rlbox_sandbox<rlbox_wasm2c_sandbox> sandbox;
  sandbox.create_sandbox("wasmsandbox");
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

void sandboxed_cgetclass(ToyInClass *c, ToyOutClass *res) {
  // printf("x is %d\n", c->x);
  rlbox_sandbox<rlbox_wasm2c_sandbox> sandbox;
  sandbox.create_sandbox("wasmsandbox");
  auto inSize = sizeof(ToyInClass);
  auto outSize = sizeof(ToyOutClass);
  tainted_toylib<ToyInClass *> tainted = sandbox.malloc_in_sandbox<ToyInClass>(inSize);
  std::memcpy(tainted.unverified_safe_pointer_because(inSize, "writing to region"),
          c, inSize);
  tainted_toylib<ToyOutClass *> taintedRes = sandbox.malloc_in_sandbox<ToyOutClass>(outSize);
  std::memcpy(taintedRes.unverified_safe_pointer_because(outSize, "writing to region"),
          res, outSize);
  //ToyInClass *in = reinterpret_cast<ToyInClass *>(tainted.unverified_safe_pointer_because(inSize, "writing to region"));
  //printf("x issss %d\n", in->x);

  // unsigned long res = sandbox.invoke_sandbox_function(c_getclass, tainted)
  //               .copy_and_verify_address([] (unsigned long r) {
  //                 return r;
  //               });
  sandbox.invoke_sandbox_function(c_getclass, tainted, taintedRes);
  ToyOutClass *out = reinterpret_cast<ToyOutClass *>(taintedRes.unverified_safe_pointer_because(outSize, "writing to region"));
  res->w = out->w;
  res->z = out->z;
  // printf("x issss %d\n", out->z);
  sandbox.destroy_sandbox();
  return;
}

void sandboxed_crevlist(int* inList, int* outList, int size) {
 // Declare and create a new wasm sandbox
  rlbox_sandbox<rlbox_wasm2c_sandbox> sandbox;
  sandbox.create_sandbox("wasmsandbox");
  size_t bSize = size*sizeof(int);
  tainted_toylib<int*> taintedIn = sandbox.malloc_in_sandbox<int>(bSize);
  std::memcpy(taintedIn.unverified_safe_pointer_because(bSize, "writing to region"),
          inList, bSize);
  tainted_toylib<int*> taintedOut = sandbox.malloc_in_sandbox<int>(bSize);
  std::memcpy(taintedOut.unverified_safe_pointer_because(bSize, "writing to region"),
          outList, bSize);
  sandbox.invoke_sandbox_function(c_revlist, taintedIn, taintedOut, size);
  int *out = reinterpret_cast<int*>(taintedOut.unverified_safe_pointer_because(bSize, "writing to region"));
  for (int i = 0; i < size; i++) {
    outList[i] = out[i];
  }
  return;
}
