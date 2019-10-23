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
2. 生产者消费者问题
```cpp
pthread_mutex_t mutux;
sem_t sem_p;
sem_t sem_c;

void producer() {
    if (buff_full) {
        sem_wait(&sem_p);
    }
    pthread_mutex_lock(&mutex);
    write_data();
    pthread_mutex_unlock(&mutex);
    sem_pos(&sem_c);
}
 
void cunsumer() {
    if (buff_empty) {
        sem_wait(&sem_c);
    }
    pthread_mutex_lock(&mutex);
    read_data();
    pthread_mutex_unlock(&mutex);
    sem_post(&sem_p);
}
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
