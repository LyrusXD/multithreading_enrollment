#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <sys/time.h>

#define TOTAL_STUDENTS 2
#define TOTAL_QUEUES 3
#define RANGE_OF_ARRIVAL_TIMES 120;
pthread_mutex_t section1Mutex;
pthread_mutex_t section2Mutex;
pthread_mutex_t section3Mutex;
pthread_mutex_t printMutex;
pthread_mutex_t section1CounterMutex;
pthread_mutex_t section2CounterMutex;
pthread_mutex_t section3CounterMutex;
sem_t queueGSSem;
sem_t queueRSSem;
sem_t queueEESem;
time_t startTime;
pthread_mutex_t queueGSMutex;
pthread_mutex_t queueRSMutex;
pthread_mutex_t queueEEMutex;
pthread_mutex_t queueGSMutexCounter;
pthread_mutex_t queueRSMutexCounter;
pthread_mutex_t queueEEMutexCounter;
int totalStudentsProcessed;
int studentIDs[TOTAL_STUDENTS];
Student queueGS[TOTAL_STUDENTS];
Student queueRS[TOTAL_STUDENTS];
Student queueEE[TOTAL_STUDENTS];

typedef struct{
  int id;
  int arrivalTime;
  int processedTime;
  int priority;
  int section;
} Student;
//Finish initializing all variables for this class

//Implement printEvent
void printEvent(Student *student,char *event){
  //may use mutexes
}

void *studentT(void *param){
  //data processing of data passed through and creation of Student object
  int val = *((int *) param);
  int priorityValue;
  int sectionValue;
  sectionValue = rand() % 3 + 1;
  priorityValue = rand() % 4 + 1;
  Student studentProfile;
  studentProfile.id = val;
  studentProfile.priority = priorityValue;
  studentProfile.section = sectionValue;
  printf("Student %d\n",studentProfile.id);
  int arrivalTime = rand() % RANGE_OF_ARRIVAL_TIMES;
  studentProfile.arrivalTime = arrivalTime;
  //randomize arrival time
  sleep(arrivalTime)

  //add to queue depending on priority via addStudentToQueue() pass by reference? or keep track through global array[student] variable?
  return NULL;
}

void addStudentToQueue(){
  //adds student to a queue if not full otherwise wait. 
  //may use mutexes and semaphores
  //print event via printEvent()
}

void *queue(void *param){
  // process student via processStudent()
  
  //may use mutexes and semaphores
}

void processStudent(){
  //add student to section if not full otherwise drop
  //print event via printEvent()
}

int main(int argc, char *argv[]){
  //Initialize all mutex and semaphores
  pthread_mutex_init(&section1Mutex,NULL);
  pthread_mutex_init(&section2Mutex,NULL);
  pthread_mutex_init(&section3Mutex,NULL);
  pthread_mutex_init(&printMutex,NULL);
  pthread_mutex_init(&section1CounterMutex,NULL);
  pthread_mutex_init(&section2CounterMutex,NULL);
  pthread_mutex_init(&section3CounterMutex,NULL);
  sem_init(&queueGSSem,0,0);
  sem_init(&queueRSSem,0,0);
  sem_init(&queueEESem,0,0);
  
  //seed the random function
  srand(time(0));
  //set the startTime variable
  time(&startTime);

  //Create student threads - do we want to store everyone somewhere?
  //As of now, create students in each thread but it will be hard to
  //output everything at the end. Maybe modify to create an array of 
  //students in the for loop iteration instead.
  int i;

  for(int i = 0; i < TOTAL_QUEUES;i++){
    pthread_t queue;
    pthread_attr_t queueAttr;
    pthread_attr_init(&queueAttr);
    pthread_create(&queue,&queueAttr,queue,NULL);
    
  }

  for(i = 0; i < TOTAL_STUDENTS; i++){
    studentIDs[i] = i+1;
    pthread_t studentThread;
    pthread_attr_t studentAttr; //Do we need this?
    pthread_attr_init(&studentAttr); //Do we need this?
    pthread_create(&studentThread, &studentAttr, studentT, &studentIDs[i]);

  }

  sleep(1);
  pthread_join(queue1,NULL);

  //Create queue threads

  //WE MAY NOT NEED THIS:set up alarm to notify something(queues) when classes are full OR 75 students processed
  
  //At the end join all queues to empty and join back to main

  /*
    Print out final statistics:
    All students in each section
    All students dropped
    Turnaround time for each student (arrival time to enrolled/dropped)
    Average turnaround time per queue
    Anything else <-- huh?
  */

}

