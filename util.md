### Cat
```cpp
cat file1.txt file2.txt > file3.txt // add file1.txt and file2.txt to file3.txt   |file1|file2|
// file3.txt    
   this is file1
   this is file2
cat file1.txt >> file3.txt   // append to end of file3.txt   |file3|file1|
// file3.txt
   this is file1
   this is file2
   this is file3
```
### DD
```
  /* Enlarge file */
  
 dd if=/dev/zero of=./gen3_uboot.bin.usb bs=1 count=1 seek=819199
```
