## 1) For the Hello Name challenge:

### a. Did you try passing your name as an argument from the command line or did you use scanf? Why?

I passed the string through the command line. It could easily work either way, but given the program was fairly simple and I only needed to take a single piece of input, I went with the command line. At a large scale, it may have been more performant to have a stack-allocated buffer that is read into via scanf, but performance was not a concern here.

### b. How did you manage or allocate the strings? (Static or dynamic)

I didn't allocate the strings, but they are managed dynamically by the OS.

## 2) For Archimedes algorithm

### a. How did you time your program?

I used clock_gettime(CLOCK_MONOTONIC_RAW, &start) to get microsecond-scale precision and then simply did arithmetic on the structs to compute the number of elapsed microseconds. I made sure to position the timing calls as closely as possibly to the actual computations to not include extra overhead like function calls.

### b. Were there any issues with precision and/or convergence that you noticed?

Yes -- for large n, the lower bound actually exceeds the true value of pi due to precision issues.

## For Matrix-vector multiplication

### a. How did you allocate and access your matrix?

I allocated/deallocated it (and the vector) dynamically with malloc() and free(). I accessed elements in the matrix by computing where they would be located in a flat array structure, i.e., element (i, j) is located at matrix[i*columns + j].

### b. Were there any challenges in reading in the file?

Yes. Reading in the full file before beginning computations felt wasteful in terms of memory, so I processed it line by line. However, this also meant that in the for-loop body I had to track which line I was on to change behavior accordingly. I also had to be sure my buffer was large enough to hold the longest provided line. Additionally, reading a dynamically-size list of integers was tricky. I decided to use the "%n" format specifier, which allows you to recover the number of characters a sscanf() call consumed. I could then reason about where the next integer would be located in the line. For example, if the first sscanf() call consumed 3 characters, I knew they would be 2 digits and 1 space, so the next integer would start at index 3.

### c. Was there anything special about the actual computation?

No, aside from assuming the number of columns in the matrix matched the number of rows.

### d. What was your strategy for timing?

Again, clock_gettime() to measure elapsed time at microsecond-level precision, where the same note about timing call location applies.

## For measuring the speed of arithmetic computations

### a. What was your timing strategy?

I used the same strategy as previously described, but I also measured timing in two different ways. In the first, I setup the code to allow for pipeline (to measure throughput). In the second, I made the result of each computation dependent on the previous, so pipeline was impossible (to measure latency). Furthermore, I inlined assembly that alerts the compiler that the assembly may modify arbitrary memory locations (though in reality it does nothign, this prevents compiler optimizations). Finally, I made sure to warm the cache before each benchmark by reading from the full array (this helps prevent unfair penalties against the first operations in the suite and other mysterious, unpredictable caching behavior).

### b. Are all arithmetic operations created equal?

No. While multiplication, division, and sqrt have similar throughputs, the latency of division is about 1.2x that of multiplication, and the latency of sqrt is about 1.5x that of multiplication. Sin is its own beast; its throughput is more than 10x slower than multiplication and its latency is about 3.5x that of multiplication.

## For the row-major/column-major exercise

### a. What did you observe about differences in program behavior in static vs dynamic allocation of arrays, and how do you explain it?

### b. What did you observe about differences in program behavior in row-major vs. column major computations and how do you explain it?

## For the string transform problem

### a. What were some alternative implementation strategies could you entertain here?

### b. What programming hazards/pitfalls should be considered in your general approach?
