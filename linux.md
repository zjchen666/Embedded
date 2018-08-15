## Process
### priority and nice
 pri比较好理解，即进程的优先级，pri越小，优先级越高，那nice值呢？nice表示进程可被执行的优先级的修正数值。如前面说的，pri越小越优先被执行，那么加入nice之后pri(new)=pri(old)+nice。这样,当nice为负值的时候，该程序的pri变小，优先级越高。  
 _nice与renice_
   1.nice的作用是启动时设置nice的值  
   2.renice的作用是修改已经存在的进程的nice值
