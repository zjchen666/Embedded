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
In Thread1:
pthread_mutex_lock(&m_mutex);   
pthread_cond_wait(&m_cond,&m_mutex);   
pthread_mutex_unlock(&m_mutex);  
 
In Thread2:
pthread_mutex_lock(&m_mutex);   
pthread_cond_signal(&m_cond);   
pthread_mutex_unlock(&m_mutex);  


3. 读者写者问题