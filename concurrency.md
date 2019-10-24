
### semphore, mutex, condition variable and event
### DeadLock
   4 conditions: 
      - mutual exclusive   Solution: Lock free Hardware
      - hold and wait      Solution: try lock
      - no-preemption      Solution: try lock
      - circle dependency. Solution: Change order
   
   
### 进程同步 Sync 
1. 交替执行
```cpp
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include <semaphore.h>

#define COUNT 100
static  int   i = 1;

static sem_t sem_a;
static sem_t sem_b;

void* thread_a(void *arg)
{
    printf("thread A created\n");
    while ((i <= COUNT))
    {
        sem_wait(&sem_a);
        if (i <= COUNT) {
            printf("thread A : %d\n",i);
            ++i;
        }
        sem_post(&sem_b);
    }
}

void* thread_b(void *arg)
{
    printf("thread B created\n");
    while ((i <= COUNT))
    {
        sem_wait(&sem_b);
        if (i <= COUNT) {
            printf("thread B : %d\n",i);
            ++i;
        }
        sem_post(&sem_a);
    }
}

int main()
{
    pthread_t tid1, tid2;

    sem_init(&sem_a, 0, 1);
    sem_init(&sem_b, 0, 0);

    pthread_create(&tid1, NULL, thread_a, NULL);
    pthread_create(&tid2, NULL, thread_b, NULL);

    sem_destroy(&sem_a);
    sem_destroy(&sem_b);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    return 0;
}
```
2. 生产者消费者问题 - 交替执行
```cpp
pthread_mutex_t mutux;
sem_t sem_p;
sem_t sem_c;

void producer() {
    sem_wait(&empty);
    // mutex 是用来处理 multiple producer和 multiple consumer的情况
    pthread_mutex_lock(&mutex);
    write_data();
    pthread_mutex_unlock(&mutex);
    sem_pos(&full);
}
 
void cunsumer() {
    sem_wait(&full);
    pthread_mutex_lock(&mutex);
    read_data();
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
}
```
应用 Ring buffer

```cpp
pthread_mutex_t mutux;
sem_t empty; // 0 - 1 semphore
sem_t full;  // 0 - 1 semphore

typedef struct {
    void* buffer;
    size_t p_index;
    size_t c_index;
    size_t size;
} ring_buf_t;

int put(ring_buf_t* buf, int val) {
    if ((buf->p_index + 1) % SIZE >= buf->c_index) {
        return ERR_BUFFER_FULL;
    }
    buf[buf->p_index] = val;
    buf->p_index = (buf->p_index + 1) % SIZE;
}

int get(ring_buf_t* buf) {
    int data;
    if (buf->c_index == buf->p_index) {
        return ERR_BUFF_EMPTY;
    }
    data = buf[buf->c_index];
    buf->c_index = (buf->c_index + 1) % SIZE;
    return data;
}

void buffer_write(int val) {
    if (buffer_full()) {
        sem_wait(&empty);
    }
    // mutex 是用来处理 multiple producer和 multiple consumer的情况
    pthread_mutex_lock(&mutex);
    put(val);
    pthread_mutex_unlock(&mutex);
    sem_pos(&full);
}
 
int buffer_read(void) {
    int res;
    if (buffer_empty()) {
        sem_wait(&full);
    }
    pthread_mutex_lock(&mutex);
    res = get();
    pthread_mutex_unlock(&mutex);
    sem_post(&empty);
    return res;
}
```

```

3. 读者写者问题
```cpp
pthread_mutex_t mutex;
pthread_mutex_t mutex_w;
int reader_count = 0;

void writer() {
    pthread_mutex_lock(&mutex_w);
    write();
    pthread_mutex_unlock(&mutex_w);
}

void reader() {
    pthread_mutex_lock(&mutex);
    reader_count++;
    if (reader_count == 1) {
        pthread_mutex_lock(&mutex_w);
    }
    pthread_mutex_unlock(&mutex);
    
    read();
    
    pthread_mutex_lock(&mutex);
    reader_count--;
    if (reader_count == 0) {
        pthread_mutex_unlock(&mutex_w);
    }
    pthread_mutex_unlock(&mutex);
}

自旋锁(Spin lock)

自旋锁与互斥锁有点类似，只是自旋锁不会引起调用者睡眠，如果自旋锁已经被别的执行单元保持，调用者就一直循环在那里看是 否该自旋锁的保持者已经释放了锁，"自旋"一词就是因此而得名。其作用是为了解决某项资源的互斥使用。因为自旋锁不会引起调用者睡眠，所以自旋锁的效率远 高于互斥锁。虽然它的效率比互斥锁高，但是它也有些不足之处：
    1、自旋锁一直占用CPU，他在未获得锁的情况下，一直运行－－自旋，所以占用着CPU，如果不能在很短的时 间内获得锁，这无疑会使CPU效率降低。
    2、在用自旋锁时有可能造成死锁，当递归调用时有可能造成死锁，调用有些其他函数也可能造成死锁，如 copy_to_user()、copy_from_user()、kmalloc()等。
因此我们要慎重使用自旋锁，自旋锁只有在内核可抢占式或SMP的情况下才真正需要，在单CPU且不可抢占式的内核下，自旋锁的操作为空操作。自旋锁适用于锁使用者保持锁时间比较短的情况下。

两种锁的加锁原理

互斥锁：线程会从sleep（加锁）——>running（解锁），过程中有上下文的切换，cpu的抢占，信号的发送等开销。
自旋锁：线程一直是running(加锁——>解锁)，死循环检测锁的标志位，机制不复杂。

互斥锁属于sleep-waiting类型的锁。例如在一个双核的机器上有两个线程(线程A和线程B)，它们分别运行在Core0和 Core1上。假设线程A想要通过pthread_mutex_lock操作去得到一个临界区的锁，而此时这个锁正被线程B所持有，那么线程A就会被阻塞 (blocking)，Core0 会在此时进行上下文切换(Context Switch)将线程A置于等待队列中，此时Core0就可以运行其他的任务(例如另一个线程C)而不必进行忙等待。而自旋锁则不然，它属于busy-waiting类型的锁，如果线程A是使用pthread_spin_lock操作去请求锁，那么线程A就会一直在 Core0上进行忙等待并不停的进行锁请求，直到得到这个锁为止。

两种锁的区别

互斥锁的起始原始开销要高于自旋锁，但是基本是一劳永逸，临界区持锁时间的大小并不会对互斥锁的开销造成影响，而自旋锁是死循环检测，加锁全程消耗cpu，起始开销虽然低于互斥锁，但是随着持锁时间，加锁的开销是线性增长。

两种锁的应用

互斥锁用于临界区持锁时间比较长的操作，比如下面这些情况都可以考虑

1 临界区有IO操作

2 临界区代码复杂或者循环量大

3 临界区竞争非常激烈

4 单核处理器

至于自旋锁就主要用在临界区持锁时间非常短且CPU资源不紧张的情况下，自旋锁一般用于多核的服务器。
