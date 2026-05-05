#include <stdio.h>

long pthFactor(long n, long p) {
    // Find the square root of n using binary search
    long root = 0;
    long low = 1, high = n;
    while (low <= high) {
        long mid = low + (high - low) / 2;
        if (mid <= n / mid) {
            root = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    // Count factors that are less than or equal to the square root
    long count_small = 0;
    for (long i = 1; i <= root; i++) {
        if (n % i == 0) {
            count_small++;
        }
    }
    
    // Total number of factors
    long total = count_small * 2;
    if (root * root == n) {
        total--;  
    }
    
    //  factors are not enough
    if (p > total) {
        return 0;
    }
    
    // Case 1: p is in the first half (small factors)
    if (p <= count_small) {
        long seen = 0;
        for (long i = 1; i <= root; i++) {
            if (n % i == 0) {
                seen++;
                if (seen == p) {
                    return i;
                }
            }
        }
    } 
    // Case 2: p is in the second half (large factors)
    else {
        // Find which small factor pairs with what we want
        long target = total - p + 1;
        long seen = 0;
        for (long i = 1; i <= root; i++) {
            if (n % i == 0) {
                seen++;
                if (seen == target) {
                    return n / i;
                }
            }
        }
    }
    
    return 0;
}

int main() {
    // Test the function with given examples
    printf("%ld\n", pthFactor(10, 3));   //  5
    printf("%ld\n", pthFactor(16, 4));   //  8
    printf("%ld\n", pthFactor(100, 9));  //  100
    
    return 0;
}