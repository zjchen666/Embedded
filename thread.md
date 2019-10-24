### 进程互斥

### 进程同步
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
pthread_mutex_t mutex_reader;
int reader_count = 0;

void writer() {
    pthread_mutex_lock(&mutex);
    write();
    pthread_mutex_unlock(&mutex);
}

void reader() {
    pthread_mutex_lock(&mutex_reader);
    reader_count++;
    if (reader_count == 1) {
        pthread_mutex_lock(&mutex);
    }
    pthread_mutex_unlock(&mutex_reader);
    
    read();
    
    pthread_mutex_lock(&mutex_reader);
    reader_count--;
    if (reader_count == 0) {
        pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_unlock(&mutex_reader);
}
