#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <strings.h>

void* secondThread(void* arg);

void main()
{
  pthread_t threadID;
  int errorNum = 0, newThread, join;
  
  printf("main thread here; pid is %d, tid is %lu\n", getpid(), pthread_self());
  newThread = pthread_create(&threadID, NULL, secondThread, "B");
  if (newThread)
  {
     printf("Error creating thread. '%s' \n", strerror(errorNum));
  }
  else
  {
     printf("main successfully created a new thread with TID of %lu \n", threadID);
  }
  join = pthread_join(threadID, NULL);

  if (join != 0)
  {
    printf("Error creating thread. %s\n", strerror(errorNum));
  }
  else
  {
    printf("main: second thread has terminated, main will now exit.\n");
  }
}

void* secondThread(void* arg)
{
  printf("    second thread here, my TID is %lu but I'm still in process %lu \n", pthread_self(), getpid());
  printf("   I received a '%s' when I was created\n",(char*)arg);
}
