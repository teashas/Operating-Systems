/********************************************************************************************************************/
/*                                                                                                                  */
/*  Program to demonstrate (by brute force! ;-) a race condition.  In the middle of a critical section, the 'main'  */
/*  thread deliberately executes a call to sleep(), which yields the CPU to some other thread, producing the        */
/*  the same result as if it (the 'main' thread) had actually been genuinely preempted at exactly that point in     */
/*  its critical section.                                                                                           */
/*                                                                                                                  */
/*  No user interaction is required to run this program.                                                            */
/*                                                                                                                  */   
/*  Compiled (gcc -lpthread) and tested by Saima Teasha on 9 Oct 2021 on prclab under Linux                           */ 
/*                                                                                                                  */ 
/********************************************************************************************************************/

/******************************************   INCLUDED FILES    *****************************************************/
#include <stdio.h>           
#include <pthread.h>          /*  Needed for the POSIX thread functions, specifically pthread_create()              */
#include <errno.h>            /*  Needed for the perror() function used for debugging system service calls          */
#include<unistd.h>            /*  Need for the sleep function                                                       */
/********************************************************************************************************************/

/****************** GLOBAL VARIABLES ********************************************************************************/
                              /*  Here is the shared resource (a global structure) over which the two threads will  */
struct                        /*  have  critical sections and a race condition. I've initialized the point's        */
{                             /*  coordinates to [0,0] and the idea is that the x and y coordinates of this point   */
  int x,y;                    /*  are always supposed be remain equal to one another after a series of updates by   */
} race_point={0,0};           /*  concurrently executing threads                                                                                                                                                                                                                                       */
pthread_mutex_t mlock;                                                    
/********************************************************************************************************************/

/****************************************************************************   Main   ******************************/
/*                                                                                                                  */
int main()                    /* 'main' is obviously  the first thread, no?  Every process must have at least one   */
{                             /*  kernel-level thread.  In C, that has to be the one that starts executing 'main'   */
   
   void *second_thread(void *);     /*  Prototype, full definition follows 'main'                                   */
 
   pthread_t new_tid_no=0;    
   int errorCode;             /*  Used to check for success or failure after the pthread_join                       */

   printf("\n Main:  Initially, race_point is [0,0]; after creating another thread, main will set it to [1,1]  \n");

   if ( pthread_create(&new_tid_no, NULL, second_thread, NULL) == 0)    /* Create another thread; check for success */
      {
         /******  Put your ENTRY SECTION code here.  ******/

	   if ((errorCode = pthread_mutex_lock(&mlock)) != 0)                                                                                         
           {
             printf("\n  Failed pthread_mutex_lock: %s", strerror(errorCode));
             return -1;
           }

         /***************  START OF MAIN'S CRITICAL SECTION where we update race_point coordinates to [1,1] *********/
            
         race_point.x=1;      /*  By sleeping here in the middle of the critical section we ensure that the second  */
                              /*  thread can start to  execute, thus simulating a genuine preemption at exactly     */
	 sleep(1);            /*  this (horribly wrong) time and guaranteeing that we'll get a race condition.      */
                              /*  Comment out the 'sleep' here and you'll see that the race condition               */
         race_point.y=1;      /*  disappears; but that's not the way I want you to fix it for this assignment! ;-)  */
         
         /***************  END OF THE CRITICAL SECTION **************************************************************/

         /******  Put your EXIT SECTION code here.   ******/

         if ((errorCode = pthread_mutex_unlock(&mlock)) != 0)

           {

             printf("\n  Failed pthread_mutex_unlock: %s", strerror(errorCode));

             return -1;

           }

    
        if ((errorCode = pthread_join(new_tid_no, NULL)) != 0)        /* Wait for the second thread to terminate   */
	    {                                                           /* before printing the results               */
	     printf("\n  Bad pthread_join: %s", strerror(errorCode));
	     return -1;
	    }
         printf("\n Main now done;");     /* Check to see if the race condition occurred and print the results      */
         if (race_point.x == race_point.y)
            printf(" x=%d and y=%d so there was no race condition\n\n", race_point.x, race_point.y); 
         else
            printf(" but since x=%d  while y=%d there *HAS* been a race condition.\n\n", race_point.x, race_point.y); 
      }

   else perror("\n No thread created ");      /* If pthread_create() was unsuccessful, print the reason             */
   /*                                                                                                               */
}  /*******************  end of function 'main' *********************************************************************/


void *second_thread(void *dummy)             /* The thread created by 'main' starts execution here.                            */
{
	                                  /******  Put your ENTRY SECTION code here. *************                          */

  int errorCode;


 if ((errorCode = pthread_mutex_lock(&mlock)) != 0)                          	                                                               

       printf("\n  Failed pthread_mutex_lock: %s", strerror(errorCode));

   race_point.x=2;                /*   CRITICAL SECTION, in which the shared resource, the                          */
   race_point.y=2;                /*   structure named 'race_point', gets updated to [2,2]                          */

                                  /******  Put your EXIT SECTION code here. **************                          */

       if ((errorCode = pthread_mutex_unlock(&mlock)) != 0)                                                                                         

           printf("\n  Failed pthread_mutex_unlock: %s", strerror(errorCode));

       else
	   printf("\n   Second thread terminating after setting race_point to [2,2]  \n");
   
} 
