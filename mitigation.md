### SW FI Mitigation:
1. redundancy check.
```cpp
    if (compare(decryption, encryption) == 0) {
        if (compare(decryption, encryption) != 0) {
            fail();
        }
    } else {
        fail();
    }
    
    // security check
```

2. control flow check.
```cpp
int check = 0;

check = check + 2;
sesitive_function1();
check = check + 3;

check = check + 5;
sesitive_function1();
check = check + 7;

if (check == 17) {
    next_function();
} else {
    fail;
}
```

3. Time of check time of use (TOCTOU)
   - check value immediately before using it.
   - check value every time if it is used more than once.
   - clean sensitive data(key) after using it.

4. use non-trivial values
   - True*/False* 3-state decision
   - SUCCESS - *
   
5. Harden memset_s and memcpy_s constant time  
6. Integer overflow.  
7. stack protection.
