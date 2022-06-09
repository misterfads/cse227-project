from ctypes import *
import pathlib

if __name__ == "__main__":
    # Load the shared library into ctypes
    libname = pathlib.Path().absolute() / "build/libsbox.so"
    c_lib = CDLL(libname)
    #print(c_lib.__dict_)
    
    # test numbers function
    c_lib.sandboxed_cmult.restype = c_float
    c_lib.sandboxed_cmult.argtypes = [c_int, c_float]
    intArg = 3
    floatArg = 4.31
    res = c_lib.sandboxed_cmult(intArg, c_float(floatArg))
    print(f'Multiplying {integer} and {flote}: {res:.3f}')

    #test strings
    c_lib.sandboxed_cgetstrlen.restype = c_int
    c_lib.sandboxed_cgetstrlen.argtypes = [c_char_p]
    res = c_lib.sandboxed_cgetstrlen(\
        create_string_buffer(b'hello'))
    print(f'String length (hello): {res:d}')

    #c_lib.sandboxed_cstrconcat.restype = c_char_p
    c_lib.sandboxed_cstrconcat.argtypes = [c_char_p, c_char_p, c_char_p]
    res = create_string_buffer(100)
    c_lib.sandboxed_cstrconcat(\
        create_string_buffer(b'foo'), create_string_buffer(b'barr'), res)
    print(f'Concatted string of foo and barr: {res.value.decode()}')

    #test classes
    class ToyInClass(Structure):
        _fields_ = [("x", c_int), ("y", c_float)]
    class ToyOutClass(Structure):
        _fields_ = [("w", c_float), ("z", c_int)] 
    
    inInstance = ToyInClass(29,7.25)
    outInstance = ToyOutClass()
    c_lib.sandboxed_cgetclass.argtypes = [c_void_p, c_void_p]
    c_lib.sandboxed_cgetclass(byref(inInstance), byref(outInstance))
    #print(cast(res, ToyOutClass).contents)
    print(f'ToyOutClass w field is {outInstance.w}, z field is {outInstance.z}')

    #test lists
    FiveIntArr = c_int*5
    c_lib.sandboxed_crevlist.argtypes = [FiveIntArr, FiveIntArr]
    inList = FiveIntArr(1,2,3,4,5)
    outList = FiveIntArr()
    c_lib.sandboxed_crevlist(inList, outList, 5)
    print('Reversed list of', list(inList), 'is:', list(outList))

