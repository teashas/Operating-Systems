#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  int i=0;
  pid_t pid;
  
  for(i = 0; i < 3; i++)
  {
  pid = fork();
    if (pid < 0)
    {
    printf("Invalid \n");
    }
    else if (pid == 0)
    {
      printf("I am child #%d, my pid is %d; my parent's pid is %d \n", i+1 , getpid(), getppid());
      if(i == 2)
      {
        execv("child2.exe", NULL);
      }
      break;
    }
    else
    {
       printf("Parent, my pid is %d: Spawned child #%d whose pid is %d \n", getpid(), i+1, pid);
    }

  }
  return 0;
}
