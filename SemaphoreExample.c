#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NO_OF_QUEUE       80	/* #of Students */
#define NO_OF_SLOTS       20
int     Q[NO_OF_SLOTS];
int     front = -1;           
int     rear  = -1;           

pthread_mutex_t mutex;        
sem_t           full;        
sem_t           empty;        


void *Supervisor(void *arg){
	int student = (int)arg;

	pthread_detach(pthread_self());
	sem_wait(&empty);             
	pthread_mutex_lock(&mutex);   
	
	rear = rear + 1;              
	if (rear >= NO_OF_SLOTS) rear = 0;		
	Q[rear] = student;

	printf("%4d. Student was called to the Presentation\n", student+1);
	pthread_mutex_unlock(&mutex);  
	sem_post(&full);               
} 


void *Student(void *arg){
	int student = 0;
    int studentsRemoved = 0;

	printf("Presentation  is started\n");

	while (studentsRemoved < NO_OF_QUEUE){
		sem_wait(&full);             
		pthread_mutex_lock(&mutex);  

		front = front + 1;           
		if (front >= NO_OF_SLOTS)	front = 0;		
		student = Q[front];
		printf(" %4d. Student is done. It was removed from the Queue \n", student+1);
		studentsRemoved++;
		
		pthread_mutex_unlock(&mutex); 
		sem_post(&empty);             
		
		
		usleep((int)(drand48()*500000));
	}
} 



int main(int argc,char *argv[]){
	int i;
	pthread_t supervisorId;
	pthread_t QUEUEId;
	
	
	srand48(time(NULL));

	pthread_mutex_init(&mutex,NULL);  
	sem_init(&full, 0, 0);             
	sem_init(&empty, 0, NO_OF_SLOTS);  

	/* supervisor thread */
	pthread_create(&QUEUEId, NULL, Student, NULL);

	
	for(i=0; i < NO_OF_QUEUE;i++){
		pthread_create(&supervisorId, NULL, Supervisor, (void *)i);
	} 

	
	pthread_join(QUEUEId, NULL);

	return 0;
} 

