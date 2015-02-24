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

typedef struct{
  int id;
  int arrivalTime;
  int processedTime;
  int priority;
  int section;
} Student;

pthread_t queueGSThread;
pthread_t queueRSThread;
pthread_t queueEEThread;
pthread_mutex_t section1Mutex;
pthread_mutex_t section2Mutex;
pthread_mutex_t section3Mutex;
pthread_mutex_t printMutex;
pthread_mutex_t section1MutexCounter;
pthread_mutex_t section2MutexCounter;
pthread_mutex_t section3MutexCounter;
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
int queueGSHeadCounter;
int queueGSTailCounter;
Student queueRS[TOTAL_STUDENTS];
int queueRSHeadCounter;
int queueRSTailCounter;
Student queueEE[TOTAL_STUDENTS];
int queueEETailCounter;
int queueEEHeadCounter;
Student studentList[TOTAL_STUDENTS];

//Finish initializing all variables for this class

//Implement printEvent
void printEvent(Student *student,char *event){
  //may use mutexes
}
void addStudentToQueue(Student *s){
  //adds student to a queue if not full otherwise wait. 
  char event[80];
  Student studentProfile = *s;
  int priority = studentProfile.priority;
  switch (priority){
  case 1:
    //in case multiple students try to add to the GS queue around the 
    //same time
    pthread_mutex_lock(&queueGSMutex);
    pthread_mutex_lock(&queueGSMutexCounter);
    queueGS[queueGSTailCounter] = studentProfile;
    queueGSTailCounter++;
    pthread_mutex_unlock(&queueGSMutex);
    pthread_mutex_unlock(&queueGSMutexCounter);
    sprintf(event, "Student %d is added to GS Queue",studentProfile.id);
    printEvent(s,event);
    sem_post(&queueGSSem);
    break;
  case 2:
    pthread_mutex_lock(&queueRSMutex);
    pthread_mutex_lock(&queueRSMutexCounter);
    queueRS[queueRSTailCounter] = studentProfile;
    queueRSTailCounter++;
    pthread_mutex_unlock(&queueRSMutex);
    pthread_mutex_unlock(&queueRSMutexCounter);
    sprintf(event, "Student %d is added to RS Queue",studentProfile.id);
    printEvent(s,event);
    sem_post(&queueRSSem);
    //add to RS
    break;
  case 3:
    pthread_mutex_lock(&queueEEMutex);
    pthread_mutex_lock(&queueEEMutexCounter);
    queueEE[queueEETailCounter] = studentProfile;
    queueEETailCounter++;
    pthread_mutex_unlock(&queueEEMutex);
    pthread_mutex_unlock(&queueEEMutexCounter);
    sprintf(event, "Student %d is added to EE Queue",studentProfile.id);
    printEvent(s,event);
    sem_post(&queueEESem);
    //add to EE
    break;
  default:
    pthread_mutex_lock(&queueEEMutex);
    pthread_mutex_lock(&queueEEMutexCounter);
    queueEE[queueEETailCounter] = studentProfile;
    queueEETailCounter++;
    pthread_mutex_unlock(&queueEEMutex);
    pthread_mutex_unlock(&queueEEMutexCounter);
    sprintf(event, "Student %d is added to EE Queue",studentProfile.id);
    printEvent(s,event);
    sem_post(&queueEESem);
    //add to EE
  }
  //print event via printEvent()
}

void *studentT(void *param){
  //data processing of data passed through and creation of Student object
  //  int val = *((int *) param);
  Student studentProfile = *((Student *)param);
  printf("Student %d\n",studentProfile.id);

  //randomize arrival time
  sleep(studentProfile.arrivalTime);
  addStudentToQueue(&studentProfile);
  return NULL;
}

void addToSection(Student *s){
    //acquire lock to section
    //acquire lock to section counter
    //add student to section
    //unlock section counter
    //unlock section
   switch(section){
    case 1:
    pthread_mutex_lock(&section1Mutex);
    pthread_mutex_lock(&section1MutexCounter);
    
    pthread_mutex_unlock(&section1MutexCounter);
    pthread_mutex_unlock(&section1Mutex);

      break;
    case 2:
      break;
    case 3:
      break;
   case 4:
     break;
   default://any section thats open
      break;
    }
}
void processStudent(){
  //add student to section if not full otherwise drop
  char startProcessingEvent[80];
  char endProcessingEvent[80];
  int processingTime;
  int priority;
  int section;
  int id;
  Student s;
  if(pthread_equal(pthread_self(),queueGSThread)){
    //calculate random wait time
    processingTime = rand() % 2 + 1;
    sem_wait(&queueGSSem);
    pthread_mutex_lock(&queueGSMutex);
    //pthread_mutex_lock(&queueGSHeadMutexCounter);
    s = queueGS[queueGSHeadCounter];
    queueGSHeadCounter++;
    pthread_mutex_unlock(&queueGSMutex);
    //pthread_mutex_unlock(&queueGSMutexCounter);
    addToSection(&s);
  }
  else if(pthread_equal(pthread_self(),queueRSThread)){
    processingTime = rand() % 3 + 2;
    //calculate random wait time
    sem_wait(&queueRSSem);
    pthread_mutex_lock(&queueRSMutex);//do we need?
    pthread_mutex_lock(&queueRSMutexCounter);//do we need?
    s = queueRS[queueRSHeadCounter];
    queueRSHeadCounter++;
    pthread_mutex_unlock(&queueRSMutex);//do we need?
    pthread_mutex_unlock(&queueRSMutexCounter);//do we need?
    addToSection(&s);
    //acquire lock to section
    //acquire lock to section counter
    //add student to section
    //unlock section counter
    //unlock section

  }
  else if(pthread_equal(pthread_self(),queueEEThread)){
    processingTime = rand() % 4 + 3;
    //calculate random wait time
    sem_wait(&queueEESem);
    pthread_mutex_lock(&queueEEMutex);//do we need?
    pthread_mutex_lock(&queueEEMutexCounter);//do we need?
    s = queueEE[queueEEHeadCounter];
    queueEEHeadCounter++;
    pthread_mutex_unlock(&queueEEMutex);//do we need?
    pthread_mutex_unlock(&queueEEMutexCounter);//do we need?
    addToSection(&s);
    //acquire lock to section
    //acquire lock to section counter
    //add student to section
    //unlock section counter
    //unlock section
    
  }
  
  //print event via printEvent()
}

void *queue(void *param){
  // process student via processStudent()
  do{
    processStudent();
  }while(totalStudentsProcessed < TOTAL_STUDENTS && (); 
  //Do we have to lock this?
  //for the totalStudentsProcessed, how do we want to trigger this?

  return NULL;
  //may use mutexes and semaphores
}


int main(int argc, char *argv[]){
  queueGSHeadCounter = 0;
  queueRSHeadCounter = 0;
  queueEEHeadCounter = 0;
  queueGSTailCounter = 0;
  queueRSTailCounter = 0;
  queueEETailCounter = 0;
  totalStudentsProcessed = 0;
  //Initialize all mutex and semaphores

  pthread_mutex_init(&section1Mutex,NULL);
  pthread_mutex_init(&section2Mutex,NULL);
  pthread_mutex_init(&section3Mutex,NULL);
  pthread_mutex_init(&printMutex,NULL);
  pthread_mutex_init(&section1MutexCounter,NULL);
  pthread_mutex_init(&section2MutexCounter,NULL);
  pthread_mutex_init(&section3MutexCounter,NULL);
  pthread_mutex_init(&queueGSMutex,NULL);
  pthread_mutex_init(&queueRSMutex,NULL);
  pthread_mutex_init(&queueEEMutex,NULL);
  pthread_mutex_init(&queueGSMutexCounter,NULL);
  pthread_mutex_init(&queueRSMutexCounter,NULL);
  pthread_mutex_init(&queueEEMutexCounter,NULL);
  sem_init(&queueGSSem,0,0);
  sem_init(&queueRSSem,0,0);
  sem_init(&queueEESem,0,0);
  
  //seed the random function
  srand(time(0));
  //set the startTime variable
  time(&startTime);

  int i;

  //Create queue threads


  pthread_attr_t queueGSAttr;
  pthread_attr_init(&queueGSAttr);
  pthread_create(&queueGSThread,&queueGSAttr,queue,NULL);

  pthread_attr_t queueRSAttr;
  pthread_attr_init(&queueRSAttr);
  pthread_create(&queueRSThread,&queueRSAttr,queue,NULL);

  pthread_attr_t queueEEAttr;
  pthread_attr_init(&queueEEAttr);
  pthread_create(&queueEEThread,&queueEEAttr,queue,NULL);
    

  //Create student threads

  for(i = 0; i < TOTAL_STUDENTS; i++){
    studentList[i].id = i+1;
    int priorityValue;
    int sectionValue;
    sectionValue = rand() % 4 + 1;
    priorityValue = rand() % 3 + 1;
    int arrivalTime = rand() % RANGE_OF_ARRIVAL_TIMES;
    studentList[i].arrivalTime = arrivalTime;
    studentList[i].priority = priorityValue;
    studentList[i].section = sectionValue;
  }
  for(i = 0; i < TOTAL_STUDENTS; i++){
    pthread_t studentThread;
    pthread_attr_t studentAttr;
    pthread_attr_init(&studentAttr);
    pthread_create(&studentThread, &studentAttr, studentT, &studentList[i]);
  }




  //WE MAY NOT NEED THIS:set up alarm to notify something(queues) when classes are full OR 75 students processed
  
  //At the end join all queues to empty and join back to main

  pthread_join(queueGSThread,NULL);
  pthread_join(queueRSThread,NULL);
  pthread_join(queueEEThread,NULL);

  /*
    Print out final statistics:
    All students in each section
    All students dropped
    Turnaround time for each student (arrival time to enrolled/dropped)
    Average turnaround time per queue
    Anything else <-- huh?
  */

}

