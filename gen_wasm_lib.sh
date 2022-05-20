wasi-sdk-12.0/bin/clang --sysroot wasi-sdk-12.0/share/wasi-sysroot/ rlbox_wasm2c_sandbox/c_src/wasm2c_sandbox_wrapper.c -c -o wasm2c_sandbox_wrapper.o
wasi-sdk-12.0/bin/clang --sysroot wasi-sdk-12.0/share/wasi-sysroot/ toylib.c -c -o toylib.o 
wasi-sdk-12.0/bin/clang --sysroot wasi-sdk-12.0/share/wasi-sysroot/ wasm2c_sandbox_wrapper.o toylib.o -Wl,--export-all -Wl,--no-entry -Wl,--growable-table -o toylib.wasm
wasm2c_sandbox_compiler/build/wasm2c -o toylibwasm.c toylib.wasm
#gcc -I wasm2c_sandbox_compiler/wasm2c/ -shared -fPIC -O3 -o libWasmFoo.so toylibwasm.c wasm2c_sandbox_compiler/wasm2c/wasm-rt-impl.c wasm2c_sandbox_compiler/wasm2c/wasm-rt-os-unix.c wasm2c_sandbox_compiler/wasm2c/wasm-rt-wasi.c

