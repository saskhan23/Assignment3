#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#define N 15

int s_buff[N];
int f=-1;
int r=-1;
sem_t mutex,nfreeBuffer,nloadedBuffer;
int p=0;
void *producer(void *ptrd){
int ptr=(int)ptrd;
int i,j;

if(p==0)

for(i=0;i<4;i++){
    sem_wait(&nfreeBuffer);//waiting conditions
    sem_wait(&mutex);
    printf("Producer : %d\n",ptr);//critical section
    r=(r+1)%N;
    if(f==-1) f=r;
    s_buff[r]=i+1;
    printf("\t");
    for ( j=0;j<5;j++)
    printf("%d \t",s_buff[j]);
    printf("\n");
    sem_post(&mutex);//posting conditions
    sem_post(&nloadedBuffer);
    sleep(1);
}
}
    void *consumer(void *ctrd){
    int ctr=(int)ctrd;
    int i,j;
    if(p==1)
    for(i=0;i<4;i++) {
    sem_wait(&nloadedBuffer);//waiting conditions
    sem_wait(&mutex);
    printf("Consumer : %d\n",ctr);//critical section
    s_buff[f]=0;
    if (f==r) f=r=-1;
    else f=(f+1)%N;
    printf("\t");
    for ( j=0;j<5;j++)
    printf("%d \t",s_buff[j]);
    printf("\n");
    sem_post(&mutex);//posting conditions
    sem_post(&nfreeBuffer);
    sleep(1);
}
}
int main() {

    sem_init(&mutex,0,1);//3 semaphores
    sem_init(&nfreeBuffer,0,N);
    sem_init(&nloadedBuffer,0,0);
    pthread_t prod_thrd[3];//threads
    pthread_t cons_thrd[3];
    int i,rc;
    //f=0;
    for(i=0;i<3;i++)
    {
    rc=pthread_create(&prod_thrd[i],NULL,producer,(void *)i);
    if(rc) break;
    }
    for(i=0;i<3;i++)
    {
    rc=pthread_create(&cons_thrd[i],NULL,consumer,(void *)i);
    if(rc) break;
    }
    for(i=0;i<3;i++)
    pthread_join(prod_thrd[i],NULL);
    for(i=0;i<3;i++)
    pthread_join(cons_thrd[i],NULL);
    
},
`
