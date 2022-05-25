#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <strings.h>

void* secondThread(void* arg);

void main()
{
  pthread_t threadID;
  int errorNum = 0, newThread;
  
  printf("main thread here; pid is %d, tid is %lu\n", getpid(), pthread_self());
  newThread = pthread_create(&threadID, NULL, secondThread, NULL);
  if (newThread)
  {
     printf("Error in creating thread '%s' \n", strerror(errorNum));
  }
  else
  {
    printf("main successfully created a new thread with TID of %lu \n", threadID);
  }
}

void* secondThread(void* arg)
{
  printf("second thread here, my TID is %lu but I'm still in process %lu \n", pthread_self(),getpid());
}
