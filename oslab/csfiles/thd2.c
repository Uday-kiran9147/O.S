#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <math.h> 

void *print_avg( void *ptr );
void *print_min( void *ptr );
void *print_max( void *ptr );
void *print_std( void *ptr );
void *print_mead( void *ptr );
/*
pthread_mutex_t mutex_avg = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_min = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_max = PTHREAD_MUTEX_INITIALIZER;
*/
void main()
{
	pthread_t thread_avg, thread_min, thread_max, thread_std, thread_mead;
	pthread_attr_t attr; /* set of attributes for the thread */

	int  iret1, iret2, iret3, iret4, iret5,i ;
	int a[7]={90,81,78,95,79,72,85};

	pthread_attr_init(&attr);

	printf("Elements of the array:\n");
	for (i=0; i<7; i++)
	printf("%d \t",a[i]);
	printf("\n\n");

	/* Create independent threads each of which will execute function */
	iret1 = pthread_create( &thread_avg, &attr,print_mead , (void*) a);
	if(iret1)
	{fprintf(stderr,"Error - pthread_create() return code: %d\n",iret1); exit(EXIT_FAILURE); }
printf("a[0]=%d \n",a[0]);
	iret2 = pthread_create( &thread_min, &attr, print_min, (void*) a);
	if(iret2)
	{ fprintf(stderr,"Error - pthread_create() return code: %d\n",iret2); exit(EXIT_FAILURE); }
printf("a[0]=%d \n",a[0]);
	iret3 = pthread_create( &thread_max, &attr, print_max, (void*) a);
	if(iret3)
	{fprintf(stderr,"Error - pthread_create() return code: %d\n",iret3); exit(EXIT_FAILURE); }
printf("a[0]=%d \n",a[0]);
	iret4 = pthread_create( &thread_std, &attr,print_avg, (void*) a);
	if(iret4)
	{ fprintf(stderr,"Error - pthread_create() return code: %d\n",iret4); exit(EXIT_FAILURE); }

printf("a[0]=%d \n",a[0]);
	iret5 = pthread_create( &thread_mead, &attr, print_std , (void*) a);
	if(iret5)
	{fprintf(stderr,"Error - pthread_create() return code: %d\n",iret5); exit(EXIT_FAILURE); }

	
	/* Wait till threads are complete before main continues. Unless we  */
	/* wait we run the risk of executing an exit which will terminate   */
	/* the process and all threads before the threads have completed.   */
        pthread_join(thread_mead, NULL); 
	pthread_join(thread_avg, NULL);
	pthread_join(thread_min, NULL); 
	pthread_join(thread_max, NULL); 
	
	
	pthread_join(thread_std, NULL); 
	exit(EXIT_SUCCESS);
}


void *print_avg( void *ptr )
{     
	int avg=0,i, *p;
	p=(int*)ptr;  // Type casting 
	
	for (i=0; i<7 ; i++)
	avg += (*(p+i));
	//printf("Thread name: Average \t Thread ID: %ld\t The average is %f.\n", &print_avg,(float) avg/7);
	printf("Thread name: Average \t Thread ID: %ld\t The average is %f.\n", pthread_self(),(float) avg/7);
	fflush(stdout); 
	pthread_exit (0) ;

}
void *print_min( void *ptr )
{     
	int minv=1000,i,*p;
	p=(int*)ptr;
	
	for (i=0; i<7 ; i++)
	{
		if (*(p+i)<=minv)
		minv=*(p+i);
	}
//	printf("Thread name: Minimum number\t Thread ID: %ld\t The min value is %d.\n",&print_min, minv);
	printf("Thread name: Minimum number\t Thread ID: %ld\t The min value is %d.\n",pthread_self(), minv);
	fflush(stdout);
	pthread_exit (0) ;
	
}

void *print_max( void *ptr )
{     
	int minv=-1000,i,*p;
	p=(int*)ptr;
	
	for (i=0; i<7 ; i++)
	{
		if (*(p+i)>=minv)
		minv=*(p+i);
	}
//	printf("Thread name: Maximum number\tThread ID: %ld\t The max value is %d.\n",&print_max,minv);
	printf("Thread name: Maximum number\tThread ID: %ld\t The max value is %d.\n",pthread_self(),minv);
	fflush(stdout); 
	pthread_exit (0) ;

}
void *print_std( void *ptr )
{

	int mn=0,i,*p;
	p=(int*)ptr;
	float mean=0.0, s_d=0.0;

	
	for (i=0; i<7 ; i++)
	mn+=*(p+i); 
	
	mean=(float) (mn/7);
	
	for(i=0; i<7;i++)
	*(p+i)=(*(p+i)-mean);
	
	for(i=0; i<7;i++)
	s_d+= (*(p+i))*(*(p+i));
	
//	printf("Thread name: Standard deviation\tThread ID: %ld\t The std value is %f.\n",&print_std,sqrt(s_d/6));
	printf("Thread name: Standard deviation\tThread ID: %ld\t The std value is %f.\n",pthread_self(),sqrt((s_d/6)));
	fflush(stdout); 
	pthread_exit (0) ;

} 

void *print_mead( void *ptr )
{
	int i,j, *p, tmp;
	p=(int*)ptr;  // Type casting 
	
	for(i=0; i<7;i++)
	{
		for(j=i+1; j<7;j++)
		{
			if(*(p+i)>=*(p+j))
			{
				tmp=*(p+i);
				*(p+i)=*(p+j);
				*(p+j)=tmp;
				
			}
		}
		printf("%d --",*(p+i)); 
	}    
	printf("\n");
//	printf("Thread name: Median\tThread ID: %ld\t The median value is %d.\n",&print_mead,*(p+3));
	printf("Thread name: Median\tThread ID: %ld\t The median value is %d.\n",pthread_self(),*(p+3));
	fflush(stdout); 
	pthread_exit (0) ;
}

