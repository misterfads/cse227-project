// ANCHOR: imports
// We're going to use RLBox in a single-threaded environment.
#define RLBOX_SINGLE_THREADED_INVOCATIONS
// All calls into the sandbox are resolved statically.
#define RLBOX_USE_STATIC_CALLS() rlbox_noop_sandbox_lookup_symbol

#include <stdio.h>
#include <cassert>
#include <rlbox/rlbox.hpp>
#include <rlbox/rlbox_noop_sandbox.hpp>

#include "cmult.h"
#include "sbox_cmult.h"

using namespace std;
using namespace rlbox;

// Define base type for mylib using the noop sandbox
RLBOX_DEFINE_BASE_TYPES_FOR(cmult, noop);


float sandboxed_cmult(int x, float y) {
// ANCHOR_END: imports
// ANCHOR: hello
  // Declare and create a new sandbox
  rlbox_sandbox_cmult sandbox;
  sandbox.create_sandbox();

// ANCHOR: add
  // call the add function and check the result:
  // auto val = sandbox.invoke_sandbox_function(cmult, 3, 4.0);
  // printf("cmult 3*4.0 = %.3f\n", val);
  float result = sandbox.invoke_sandbox_function(cmult, x, y)
                    .copy_and_verify([](float ret){
      printf("Adding... 3+4 = %.3f\n", ret);
      return ret;
    });

// ANCHOR_END: add


// ANCHOR: main-end
  // destroy sandbox
  sandbox.destroy_sandbox();

  return result;
}
// ANCHOR_END: main-end
