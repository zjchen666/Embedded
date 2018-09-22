## [C++ STL](#stl)
[Misc](#misc)   
[String](#string)   
[Stack](#stack)  
[Vector](#vector)  
[pair](#pair)  
[priority_queue](#priority_queue)
## [C++ Class](#class)

## stl
| vector        | string      | deque         | stack | queue      | priority_queue | unordered_set | unordered_map |
| ------------- |-------------|:-------------:| -----:| -----------|----------------|---------------|---------------|
| push_back     | push_back   | push_back     | push  |  push      | push           | insert        | N/A           |
| pop_back      | pop_back    | pop_back      | pop   |  pop       | pop            | erase         | erase         |
| N/A           | N/A         | push_front    | N/A   |  N/A       | N/A            |               |               |
| N/A           | N/A         | pop_front     | N/A   |  N/A       | N/A            |               |               |
| front         | front       | front         | top   |  front     | top            |               |               |
| back          | back        | back          | N/A   |  back      | N/A            |               |               |
| size          | size        | size          | size  |  size      | size           |               |               |
| empty         | empty       | empty         | empty |  empty     | empty          |               |               |
| find -> end() | find -> npos|               |       |            |                |               |               |

### misc
### Initialization
```cpp
    /* hashmap */
    unordfered_map<int, int> map = {{1, 2}, {3, 4}, {5, 6}};
    
    /* pair */
    vector<pair<int, int>> pair = {{1, 2}, {1, 2}}
    
    /*2D vector*/
    int m = 2, n = 5;
    vector<vector<int>> vec(m, vector<int> (n, 2));
```
### swap：  
swap（x, y）

### sort()   
sort(a.begin(), a.end());  
sort(a.rbegin(), a.rend());  
sort(data.begin(), data.end(), greater< int >());
   
### comparator
```cpp
struct compare {
    bool operator()(const ListNode* l, const ListNode* r) {
        return l->val > r->val; // reversed
        return l->val < r->val; // not reversed
    }
};
```
### iterator
iterator is a pointer.
```cpp
        for (string::reverse_iterator it = s.rbegin(); it < s.rend(); it++)
        {
            res.push_back(*it);
        }
        reverse() 区间 [first,last)
        
        for (auto it = map.begin(); it != map.end(); it++){
            it->first; // key
            it->second; // values
        }
 ```
### auto:
### vector:
```cpp
   vector<int> nums
   iterator nums.begin(), nums.end()
   vector<int> map(26,0) -- Init a vector size 26 value 0
   //2D vector initialization
   vector<vector<int>> f(3, vector<int>(3, 0x3));
   vector<string>

   vector<double>

   size()

   push_back()
   back()
   pop_back() - doesn't return any value
```
### pair:
```cpp
    make_pair((x, y))
    a.first, a.second
```
### list:
### stack:
```cpp
   stack int s;
   s.push(1)
   s.pop() - Doesn't return any value. top first then pop.
   s.top()
```
### deque:
### sort:
```cpp
// sort algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector

bool myfunction (int i,int j) { return (i<j); }

struct myclass {
  bool operator() (int i,int j) { return (i<j);}
} myobject;

int main () {
  int myints[] = {32,71,12,45,26,80,53,33};
  std::vector<int> myvector (myints, myints+8);               // 32 71 12 45 26 80 53 33

  // using default comparison (operator <):
  std::sort (myvector.begin(), myvector.begin()+4);           //(12 32 45 71)26 80 53 33

  // using function as comp
  std::sort (myvector.begin()+4, myvector.end(), myfunction); // 12 32 45 71(26 33 53 80)

  // using object as comp
  std::sort (myvector.begin(), myvector.end(), myobject);     //(12 26 32 33 45 53 71 80)

  // print out content:
  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
```
### priority_queue:
#### define
```cpp
   Min Heap: priority_queue<int, vector <int>, greater<int>> min_heap;    
   Max Heap: priority_queue<int> max_heap;  
   Heap with self defined comparator: priority_queue<int, vector <int>, cmp> heap; //cmp 是第三个参数
```
### unordered_map:
```cpp
   unordered_map<char, int> map;
   if (map.find(key) != map.end())
```
### unordered_set:
```cpp
   unordered_set<char> set;
   if (set.find(key) != set.end())
   set.insert(val)
   set.delete(val)
```
### string:
```cpp
   string s, s.push_back(), s.size(), s.pop()
   isalnum(c), isdigit(c), isalpha(c), tolower(c)
   // find
   s.find(a) != string::npos;
   str.substr(start_pos, len) - python str[start:end]
   // add
   s + "sdsdsa" // is supported by CPP， 字符串操作
   s.push_back() // char 类型操作
   // replace
   s.replace(pos, len, str);
   
   // digital char to int convert
   int -> char: c + '0'
   char-> int: c - '0'
   
   // string compare
   string1 > string2
```

### queue:
```cpp
    queue <int> q
    q.pop()
    q.push()
    q.back()
    q.front()
```
   
定义queue对象的示例代码如下：

queue<int> q1;

queue<double> q2;

queue的基本操作有：

入队，如例：q.push(x); 将x接到队列的末端。

出队，如例：q.pop(); 弹出队列的第一个元素，注意，并不会返回被弹出元素的值。

访问队首元素，如例：q.front()，即最早被压入队列的元素。

访问队尾元素，如例：q.back()，即最后被压入队列的元素。

判断队列空，如例：q.empty()，当队列空时，返回true。

访问队列中的元素个数，如例：q.size()

### class
### public, protected, private
 1. 成员变量：   
    public - 可以被任意调用  
    protected - 子类和内部函数调用  
    private - 只能内部函数调用  
 2. 继承方式：   
    public - public->public, protected->protected, private->private.  
    protected - public->protected, protected->protected, private->private.  
    private - public->private, protected->private, private->private. 
    
### new、delete、malloc、free
   new - 调用类的构造函数
   delete - 调用类的析构函数
   malloc - 分配内存
   free  - 释放内存
   
### delete与 delete []区别
    delete - 析构一个元素
    delete[] - 析构一个元素数组。
```cpp
MemTest *mTest1=new MemTest[10];

MemTest *mTest2=new MemTest;

Int *pInt1=new int [10];

Int *pInt2=new int;vector

delete[]pInt1; 

delete[]pInt2; 

delete[]mTest1;

delete[]mTest2;// - 出错

```

### 格式化输出：
```cpp
Int ("%d"): 32 Bit integer
Long ("%ld"): 64 bit integer
Char ("%c"): Character type
Float ("%f"): 32 bit real value
Double ("%lf"): 64 bit real value
```

### 析构和构造函数
   定义一个对象时先调用基类的构造函数、然后调用派生类的构造函数；析构的时候恰好相反：先调用派生类的析构函数、然后调用基类的析构函数。

## Pointer and array
### 数组指针和指针数组
   int array[3][3]   
   int * p[3] - 指针数组， 是数组  
   (int**) p 不能和 array 互相赋值   
   int (*p)[3] 数组指针， 指向数组 可以和 array 互相赋值， 二维矩阵名其实就是数组指针  

### Const
   int * const p - 指针指向地址不能改  
   int const *p - 指向地址内容不能改

