from ctypes import *
import pathlib
import time
import matplotlib.pyplot as plt

if __name__ == "__main__":
    # Load the shared library into ctypes
    libname = pathlib.Path().absolute() / "build/libsbox.so"
    c_lib = CDLL(libname)
    #print(c_lib.__dict_)

    #try list sizes 2,4,8,16,32,64,128,256,512, 1024
    listSizes = [i*10 for i in range(5,10050,50)]
    #for each size:
        # import time, x = time.perf_counter(), y-x
        # call the sandbox function and store time taken
        # call the c code directly and store time taken
        #matplotlib both results (onto same plot)
    resSandbox = []
    res = []
    for i in listSizes:
        #print(i)
        cList = c_int*i
        c_lib.sandboxed_crevlist.argtypes = [cList, cList]
        inList = cList()
        outList = cList()
        start = time.perf_counter()
        c_lib.sandboxed_crevlist(inList, outList, i)
        end = time.perf_counter()
        elapsed = end - start
        #print('Time taken for size', i, "list:", elapsed)
        resSandbox.append(elapsed)
        c_lib.c_revlist.argtypes = [cList, cList]
        start = time.perf_counter()
        c_lib.c_revlist(inList, outList, i)
        end = time.perf_counter()
        elapsed = end - start
        res.append(elapsed)

    # diff = [resSandbox[i] - res[i] for i in range(len(res))]
    #print(listSizes)
    #print(res)
    #print(diff)

    libname = pathlib.Path().absolute() / "build/libwasmsbox.so"
    c_lib = CDLL(libname)
    #try list sizes 2,4,8,16,32,64,128,256,512, 1024
    listSizes = [i*10 for i in range(5,10050,50)]
    #for each size:
        # import time, x = time.perf_counter(), y-x
        # call the sandbox function and store time taken
        # call the c code directly and store time taken
        #matplotlib both results (onto same plot)
    resWasm = []
    for i in listSizes:
        #print(i)
        cList = c_int*i
        c_lib.sandboxed_crevlist.argtypes = [cList, cList]
        inList = cList()
        outList = cList()
        start = time.perf_counter()
        c_lib.sandboxed_crevlist(inList, outList, i)
        end = time.perf_counter()
        elapsed = end - start
        #print('Time taken for size', i, "list:", elapsed)
        resWasm.append(elapsed)

    plt.plot(listSizes,resSandbox, color="blue", label = "Sandboxed No-op")
    plt.plot(listSizes, resWasm, color = "green", label = "Sandboxed Wasm")
    plt.plot(listSizes, res, color = "red", label = "No Sandbox")
    plt.title("Program Execution Time Based on Input List Size")
    plt.xlabel("List Size")
    plt.ylabel("Execution Time")
    plt.legend()
    plt.show()




