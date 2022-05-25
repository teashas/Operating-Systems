#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

int input = 0;

void *secondThread(void *);

void main()
{
	pthread_t threadID;
	int errorNum = 0, newThread;
	printf("Main: PID is %d\n", getpid());
	newThread = pthread_create(&threadID, NULL, secondThread, NULL); 
	if(newThread!=0)
	{
		 printf("Error creating thread %s\n", strerror(errorNum));	
	}
	else
	{
		    printf("Main: Successfully created a thread with TID of %lu \n", threadID);
	}
	printf("Main: Enter a non-zero integer so that the other thread can get out of its spin loop:\n");
	scanf("%d", &input);
	while(input!=0);
	printf("Main: Second thread has re-zeroed the shared variable, so I'm done.\n");
}	
void* secondThread(void* argu)
{
  	printf("    Second thread: My TID is %lu, still in process %lu \n\n");
    printf("    I'm about to spin until main enters a non-zero value into the shared variable.\n", pthread_self(),getpid());

	while(input ==0);
	printf("    Second thread: Main set the shared variable to %d; I'll set it back to zero and then I'm done.\n", input);
	input = 0;
		


}
