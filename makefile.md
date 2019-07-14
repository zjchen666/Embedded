## $@ $< $^
$@ is the name of the file being generated,
and $< the first prerequisite (usually the source file). You can find a list of all these special variables in the GNU Make manual.

For example, consider the following declaration:

```cpp
all: library.cpp main.cpp
```
In this case:

$@ evaluates to all  
$< evaluates to library.cpp  
$^ evaluates to library.cpp main. 
