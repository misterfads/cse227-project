from ctypes import *
import pathlib

if __name__ == "__main__":
    # Load the shared library into ctypes
    libname = pathlib.Path().absolute() / "build/libsbox.so"
    c_lib = CDLL(libname)
    #print(c_lib.__dict_)
    
    # test numbers function
    c_lib.sandboxed_cmult.restype = c_float
    res = c_lib.sandboxed_cmult(3, c_float(4.31))
    print(f'Mult product (python): {res:.3f}')

    #test strings
    c_lib.sandboxed_cgetstrlen.restype = c_int
    c_lib.sandboxed_cgetstrlen.argtypes = [c_char_p]
    res = c_lib.sandboxed_cgetstrlen(\
        create_string_buffer(b'hello'))
    print(f'String length (python): {res:d}')

    #c_lib.sandboxed_cstrconcat.restype = c_char_p
    c_lib.sandboxed_cstrconcat.argtypes = [c_char_p, c_char_p, c_char_p]
    res = create_string_buffer(100)
    c_lib.sandboxed_cstrconcat(\
        create_string_buffer(b'foo'), create_string_buffer(b'barr'), res)
    print(f'Concatted string (python): {res.value.decode()}')

    #test lists


    #test classes
