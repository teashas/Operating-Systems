/*******************************************************************************
*  Saima Teasha
*  CS125
*  program HW1
*
*  a program in C that creates (spawns or forks (Links to an external site.)) 
*  three children. Each time through the spawning loop, in addition to 
*  spawning/forking a child, the parent process prints out a line that:
*      - Identifies the process that is printing the line as the parent process
*      - Provides the process identifier of the printing process (the parent)
*      - States which of the three children it just forked
*      - Provides the process identifier of the new child process that it just 
*        created
*  Have each child process just print one line that:
*      - Identifies the process that is printing the line as a child process
*      - Indicates which child it is (there are going to be three of them, right?)
*      - Provides its (the child process's) process identifier
*      - Provides its parent's process identifier.
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  int i =0;
  pid_t pid = 0;
  int ppid = getpid();
  for (i = 1; i <= 3; ++i) 
  {
    if(ppid == getpid()) 
    {
      pid = fork();
      if(pid < 0) 
      {
        printf("ERROR \n");
      } 
      else if((pid == 0)) 
      {
        printf("  I am child #%d, my pid is %d; my parent's pid is %d \n", i, getpid(), getppid()); 
        if (i == 2)
        {
          execv("child2Replacement.exe", NULL);
        }
      } 
      else 
      {
        printf("Parent, my pid is %d: Spawned child #%d whose pid is %d \n", getpid(), i, pid);
      }
    }
  }
  
  return 0;
}
