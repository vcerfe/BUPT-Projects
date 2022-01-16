#ifndef EQU_H
#define EQU_H

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

struct order
{
    char rw;       //读写进程标志
    int spendtime; //读写时间
};

struct task
{
    int spendtime;
    int p_id;
    FILE *file;
};

extern int shared_data; //共享数据
extern int read_count;  //读者数量
extern sem_t wrt;       //互斥变量，用于控制对缓冲区的访问，初始化为 1
extern sem_t cs_read;   //互斥变量，表示读者排队信号，初始化为 1
extern sem_t mutex_r;   //互斥变量，控制 read_count 的互斥访问，初始化为 1

void *writer(void *param);

void *reader(void *param);

void simulate(FILE *file, const std::vector<order> &orders);

#endif //EQU_H
