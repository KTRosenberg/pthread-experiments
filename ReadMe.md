### POSIX Thread Testing

January 2017

Karl Toby Rosenberg

- simple tests for pthread performance
using the example of a running multiplication
across a global 2D array 
- multi-threaded algorithm compared with a one-thread version, 
product is not meant to be correct (overflow / just an operation to do)

- the multi-threaded result is usually worse with a smaller data-set,
and sometimes significantly worse at -03 compilation due to optimization of
the multiplication operations. 
- Multithreading is only an "improvement" when the default (no 0 compiler flag) 
setting is used.
- The lesson is that multithreading requires a serious application
to be an efficient solution.  
- This is not the ideal use case; the testing was more for 
implementation practice.

- run with make, clean with make clean
