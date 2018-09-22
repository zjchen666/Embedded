

* [hash table and hash set](#hash)
* [array](#array) 
* [string](#string)
* [lib](#lib)
* [math](#math)

### value
正无穷 - float("inf"), 
负无穷 - float("-inf")

### math
  divide 取整分类：
  - 向下向上取整： math.floor() math.ceil()
  - 向零取整：int()
  - // 向下取整
  - / 精确除法（python3）， 向下取整（python2）

### hash
- if i not in dict() 要比 if i in dict() 耗时。前者O（n）后者O（1）。
   用 if None == dict.get() 最快
- hash table 取value的操作：hash.get(key)
- Set
  set(str) 是取string 不重复的字符。
>>> a = set("a,b,c")
>>> a
set(['a', 'c', 'b', ',']
  
  set([str]) 是将一个字符串加到set里
  set(a)
  set(['a', 'c', 'b'])
* hash table  可以存储link list 的node
* list 不能用做hash的key。__list is unhashable__.
* for key in hash 注意是key不是val。
* dict.clear() 删除字典中所有元素
* dict.copy() 返回字典(浅复制)的一个副本
* dict.get(key,default=None) 对字典dict中的键key,返回它对应的值value，如果字典中不存在此键，则返回default 的值(注意，参数default 的默认值为None)
* dict.has_key(key) 如果键(key)在字典中存在，返回True，否则返回False
* dict.items() 返回一个包含字典中(键, 值)对元组的列表
* dict.keys() 返回一个包含字典中键的列表
* dict.values() 返回一个包含字典中所有值的列表
* del dict[key] 删除一个元素。

setdefault() 和 get() 区别, 
- setdefault() 如果键不存在于字典中，将会添加键并将值设为默认值。
- get() 如果键不存在字典中 返回一个指定的默认值。

### array
- 二维数组预定义：
```python
matrix = [[0 for i in range(3)] for i in range(3)]
```
以下仅用于创建一维数组，每一个obj都是一样的
```python
>>> a = [[1]] * 5
>>> a
[[1], [1], [1], [1], [1]]
>>> a = [1] * 5
>>> a
[1, 1, 1, 1, 1]
```
- 二维list数组扩大 
```python
   array = []
   array.append([])
   array[0].append(x)
```
- 所有括号外的运算符都要空格
```python
   list[i] % list[j]
```
- 赋值， shallow copy 和 deep copy。
```python
  a = [1,2,3]
  b = a #改变a， b的值会跟着变，因为它们指向同一个对象
  b = copy.copy(a)  #改变a， b不变， copy会生成一个新的对象
  b = deepcopy.copy(a) #改变a， b不变， copy会生成一个新的对象
  
  The difference between shallow and deep copying is only relevant for compound objects
  a = [[1,2,3], [1,2,3]]
  b = copy.copy(a) #改变a[i]， b跟着变， copy会生成一个新的对象，inner object和a是一样的
  b = copy.deepcopy(a) #改变a[i]， b不变， deepcopy 会复制所有的的对象
```
### string
  可以使用 sorted(str) 为字符串排序。 不能用str.sort()， 因为字符串是immutable。 sorted()会create a new character list.
  use "".join(sorted(str)) to get a sorted new string.
  
  去除某个字符： lstrip(), rstrip(), strip()
  
### lib
* binary search
```python
     import bisect
     # input array 必须是sorted
     # array[index:] >= val
     index = bisect.bisect_left(array, val)
     # array[index:] > val
     index = bisect.bisect_right/bisect.bisect(array, val)
     # 查找并插入
     bisect.insort_left(array, val)
     bisect.insort_right(array, val)/bisect.insort(array, val）
```
* priority queue
