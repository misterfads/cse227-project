# cse227-project
## Project proposal
### What problem are you trying to address?
CPython is the reference implementation of Python. Python code is compiled to bytecode and then interpreted to execute. This has significant overhead. CPython also  has a foreign function interface with C/C++. This enables developers to write libraries in C/C++ and write a wrapper to interface with CPython. This allows developers to get the best of both worlds with Python like syntax and C/C++ code performance. 
These libraries could have security exploits which an attacker may leverage to compromise the application. Sandboxing the interface between the library and application will provide software based fault isolation and enable privilege separation.

### How are you going to address it?
We plan to leverage RLBox for this purpose. RLBox compiles C code to WebAssembly and then back to C and this runs within the same process. RLBox has a C++ API which can be leveraged to do this. We plan to first try it out on a sample C library with a python wrapper and then experiment on other 3rd party libraries written in C.

### How have others tried to address this problem? And what are their limitations?
Literature Survey: Our project has some similarities with the Retrofitting Fine Grain Isolation in the Firefox Renderer by S. Narayan et al. from lecture. This paper also uses RLBox, using it instead to isolate third party libraries used in the Firefox web browser. In our project, we will instead be using RLBox to sandbox the C/C++ library being used within our Python program.

### How are you going to evaluate your work?
1. Qualitatively answer what are the challenges involved in doing so and how is it different from doing it for Firefox
2. Measure overhead of running the sandbox
3. Qualitatively determine how portable is the approach -  can this be automated? How much work is it to do it for multiple libraries?

### How will you know if you have failed or succeeded?
If we manage to sandbox without breaking functionality of the application then we will know we have succeeded.

###
Steps to build
```
mkdir build
cd build
cmake ../
cd ../
python3 cmult.py
```
