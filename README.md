# Karatsuba Algorithm in C 🚀

**Efficient multiplication using divide-and-conquer: O(n^1.58) vs O(n²)**

## What it does
Multiplies large numbers by splitting into high/low halves, computing only 3 multiplications instead of 4.

## Demo
Multiplying 1234 * 5678
Karatsuba result: 7006652
Built-in result: 7006652

## Compile & Run
gcc karatsuba.c -lm -o karatsuba
./karatsuba

## Time Complexity
Traditional: O(n²)
Karatsuba: O(n^1.58)

#CProgramming #Algorithms #DSA
