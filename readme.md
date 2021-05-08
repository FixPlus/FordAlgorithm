# Ford Algorythm

## building
    ./build.sh

## run tests
    ./test.sh

## description
There is 3 executable files named FordAlgorithm, Generator, PerfChecker

### FordAlgorithm
applies ford algorithm to given graph. Finds the shortest path and displays it
#### usage:
    FordAlgorithm <filename> <vertex1> <vertex2> <thread count>
where *filename* is path to file with graph data in it, *vertex1* is vertex from which to look a path to *vertex2*
*thread count* specifies count of threads be used in parallel calculation
#### output
Example of output:

    FordAlgorithm.exe test1.txt 3 10 12
    Graph has been read
    Dist map for 3: 1(11) 2(10) 3(0) 4(10) 5(6) 6(5) 7(9) 8(16) 9(7) 10(10) 11(10) 12(8) 13(4) 14(6) 15(10) 16(9) 17(8) 18(7) 19(11) 20(9) 21(9) 22(8) 23(10) 24(7) 25(4) 26(3) 27(6) 28(4) 29(10) 30(7) 31(6) 32(11) 33(1) 34(7) 35(12) 36(9) 37(2) 38(6) 39(4) 40(4) 41(11) 42(2) 43(7) 44(6) 45(5) 46(5) 47(4) 48(5) 49
    (8) 50(3)
    3 10
    Calculated path from 3 to 10 : 3 -(4)-> 13 -(1)-> 46 -(5)-> 10

### Generator
generates pseudo-random graph with given number of vertices and sparsity coefficient and saves it to given file in appropriate format
#### usage:
    Generator <filename> <vertex count> <sparsity(2 - 32)>
where *filename* is path to file to save graph to, *vertex count* is desired size of graph, *sparsity* determines how much edges there would be generated (more sparse -> fewer edges)
#### output
outputs generated graph into file

    Generator.exe test10.txt 10 2

internals of *test10.txt* after that:

    1: 3 (5) 7 (7) 8 (12) 10 (3) ; 2: 4 (6) 5 (2) 6 (3) 8 (2) 10 (14) ; 3: 1 (11) 3 (7) 4 (4) 9 (2) ; 4: 5 (5) 7 (12) 8 (13) 9 (10) ; 5: 2 (2) 3 (13) 4 (7) 6 (6) 10 (12) ; 6: 5 (12) 10 (5) ; 7: 1 (12) 2 (14) 6 (3) 9 (6) ; 8: 4 (4) 7 (12) 8 (8) 10 (9) ; 9: 2 (4) 3 (10) 7 (1) 9 (8) 10 (8) ; 10: 9 (10) ; 

### PerfChecker
generates random graphs of different size and records the time of execution of ford algorithm on them
#### usage

    PerfChecker <thread count[1, 12]> <max graph size[1, 32]> <sparsity[1, 32]>

where *thread count* defines how many parallel workers will execute algorithm, *max graph size* is binary logarithm of last graph size (graphs being tested begin from size of 2 and it doubles every iteration), *sparsity* same as *Generator* argument

#### output

    PerfChecker.exe 12 3 4
    Initialize tests with 12 threads active, sparsity of all graphs = 4
    Vertex count 2 graph in calculation...Done! Time elapsed: 0ms
    Dist map for 1: 1(0) 2(inf)
    
    Vertex count 4 graph in calculation...Done! Time elapsed: 0.9974ms
    Dist map for 1: 1(0) 2(6) 3(inf) 4(8)
    
    Vertex count 8 graph in calculation...Done! Time elapsed: 1.5654ms
    Dist map for 1: 1(0) 2(16) 3(inf) 4(11) 5(5) 6(2) 7(18) 8(25)
    
    Perf check finished. results:
    Vertex count : time elapsed
    2 : 0ms
    4 : 0.9974ms
    8 : 1.5654ms

