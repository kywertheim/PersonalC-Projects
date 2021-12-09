# PersonalCppProjects
This repository contains various C++ programs, including recursion, dynamic programming (memorisation and tabulation), and genetic algorithms (binary and continuous).

1. Fibonacci.cpp

This program can calculate any Fibonacci numbers up to the 92nd number (93rd if you consider zero the first number in the Fibonacci sequence). There are three algorithms for the same task: recursion by brute force, recursion with memorisation, and tabulation.

Software requirements: C++ version 9.3.0, g++ version 9.3.0, and Ubuntu 20.04.3 LTS.

Modules: Standard Input/Output Streams Library.

To get started, please open the Terminal application, switch to the directory containing the source code, and enter the following to compile and run the program:

g++ Fibonacci.cpp -o Fibonacci

./Fibonacci

2. GA_binary.cpp

This genetic algorithm maximises the function 'f(x) = -(x^2)/10 + 3x'. It encodes the potential solutions as binary integers, so the chromosomes will be sequences of bits. A chromosome's fitness relative to the population's total fitness will determine the probability that it will reproduce.

Software requirements: C++ version 9.3.0, g++ version 9.3.0, and Ubuntu 20.04.3 LTS.

Modules: Standard Input/Output Streams Library, C Standard General Utilities Library, C Numerics Library, C String Library, C Time Library, and Numeric Limits Library.

To get started, please open the Terminal application, switch to the directory containing the source code, and enter the following to compile and run the program:

g++ GA_binary.cpp -o GA_binary

./GA_binary


3. GA_continuous.cpp

This genetic algorithm minimises the function 'f(x, y) = xsin(4x) + 1.1ysin(2y)'. It encodes each potential solution as a pair of real numbers between 0 and 10. In each generation, the top half of the chromosomes will be retained and they will reproduce the other half of the new generation. The crossover function implements Haupt's method.

Software requirements: C++ version 9.3.0, g++ version 9.3.0, and Ubuntu 20.04.3 LTS.

Modules: Standard Input/Output Streams Library, C Standard General Utilities Library, C Numerics Library, C String Library, C Time Library, and Numeric Limits Library.

To get started, please open the Terminal application, switch to the directory containing the source code, and enter the following to compile and run the program:

g++ GA_continuous.cpp -o GA_continuous

./GA_continuous
