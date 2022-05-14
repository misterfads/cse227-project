import ctypes
import pathlib

if __name__ == "__main__":
    # Load the shared library into ctypes
    libname = pathlib.Path().absolute() / "build/libsbox.so"
    c_lib = ctypes.CDLL(libname)
    #print(c_lib.__dict_)
    
    c_lib.sandboxed_cmult.restype = ctypes.c_float
    res = c_lib.sandboxed_cmult(3, ctypes.c_float(4.0))
    print(f'{res:.3f}')
