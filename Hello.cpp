#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define N 4//线程个数
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//互斥访问临界区的锁
int count = 0;//全局变量,多线程并发对它加操作，为临界资源 
void *thread_fun();//线程执行体
int main(int argc, char **argv)//主进程主 线程
{
    int i, rtn[N];//线程标识
    pthread_t thread_id[N]; //N 个线程

    for(i=0;i<N;i++) //主进程创建 N 个子线程
    {
        rtn[i] = pthread_create(&thread_id[i], NULL, &thread_fun, NULL);
    }
    for(i=N-1;i>=0;i--) //主进程等待 N 个子线程结束后再退出
    {
        pthread_join(thread_id[i], NULL);
    }
    pthread_exit(0);//主线程结束
}

void *thread_fun()
{
    count++; //共享变量 +1 操作，临界代码
    //sleep 作用：
    //1.将进程挂起 1 秒，将从执行态转到静止就绪，这时 OS 会调度其他线程运行；观察
    //count 是否正确变化；
    //2. 然后 sleep 1 秒到了,产生中断,内核收到中断后修改线程的运行状态,线程由静
    //止就绪进入活动就绪队列等待被调度
    sleep(1); //临界代码
    printf("count = %d\n", count); //临界代码
}