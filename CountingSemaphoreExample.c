#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define NO_OF_QUEUE      80		/* #of Students in queue */
#define NO_OF_SLOTS      20    	/* Lab Capacity  */

int     Q[NO_OF_SLOTS];
int     front = -1;           
int     rear  = -1;           
int c = 0;						/*Counting sem*/

pthread_mutex_t mutex;        
sem_t           full;         
sem_t           empty;        


void *Supervisor(void *arg){
	while( c < -5) {			/* Supervisor limit */
	int student = (int)arg;

	pthread_detach(pthread_self());
	sem_wait(&empty);             
	pthread_mutex_lock(&mutex);   	
	rear = rear + 1;              
	if (rear >= NO_OF_SLOTS){
	rear = 0;
	}
	Q[rear] = student;

	printf("%4d.Student was called to the presentation \n", student+1);
	pthread_mutex_unlock(&mutex);  
	sem_post(&full);   		
	  }      
	c--;
	printf(" Counting value  c after decremented by Supervisor : %d\n",c); 
} 

void *Student(void *arg){
	int student = 0;
    int studentRemoved= 0;

	printf("Presentations started \n");

	while (studentRemoved < NO_OF_QUEUE){
		sem_wait(&full);             	
		pthread_mutex_lock(&mutex);  
	
		front = front + 1;           
		if (front >= NO_OF_SLOTS  )	front = 0;		
		student = Q[front];
		printf("%4d. Student is done. He was removed from the queue \n", student+1);
		studentRemoved++;
		
		pthread_mutex_unlock(&mutex); 	
		sem_post(&empty);             
		
		c++;
		printf("Counting value after the  c incremented by the Student : %d \n",c);
		
		usleep((int)(drand48()*500000));
	} 
	
} 


int main(int argc,char *argv[]){
	int i;
	pthread_t supervisorid;
	pthread_t queueId;
	
	
	srand48(time(NULL));

	pthread_mutex_init(&mutex,NULL);   
	sem_init(&full, 0, 5);             
	sem_init(&empty, 0, NO_OF_SLOTS);  
    
	/* Supervisor Thread */
	pthread_create(&queueId, NULL, Student, NULL);

	
	for(i=0; i < NO_OF_QUEUE;i++){
		pthread_create(&supervisorid, NULL, Supervisor , (void *)i);
	} 

	
	pthread_join(queueId, NULL);


} 

