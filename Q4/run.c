#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<time.h>
#include<gsl/gsl_rng.h>
pid_t pid;
int main()
{
	void overwriteParent(int sig);
	void overwriteChild(int sig);
	struct timespec delay;
	delay.tv_sec = 0;
	delay.tv_nsec=500000000L;

	/*struct sigaction parent;
	memset(&parent, 0, sizeof(parent));
	parent.sa_handler = overwriteParent;
*/

	const gsl_rng_type * type;
	gsl_rng * random;
	gsl_rng_env_setup();
	type = gsl_rng_default;
	random = gsl_rng_alloc (type);
	if (random == NULL)
	{
	fprintf(stderr, "\nNot enough space to allocate in the memory\n");
	exit(1);
	}
	int u;
	int j;
	int sig;
	pid = fork();
	if (pid < 0)
	{
		fprintf(stderr,"\nFork failed!");
		exit(1);
	}
	else if (pid == 0)
	{
		//in child
		signal(sig,&overwriteChild);
		
		for(;;)
		{
			printf("\nChild waiting");
			if (nanosleep(&delay, NULL))
			{
				perror("\nnanosleep");
				return 1;
			}
		}
	}
	else
	{
		//in parent
		gsl_rng_set(random,time(NULL));
		sleep(1);
		for(;;)
		{
			u = gsl_rng_get(random);
			j = abs(u%31);
			sig = j+1;
			signal(sig,overwriteParent);
			/*if(signal(sig,&overwriteParent)== SIG_ERR)
		        {
               			printf("Error");
				exit(2);
			}*/
			printf("\nParent sending signal %d",sig);
			kill(pid,sig);
			if (nanosleep(&delay, NULL))
			{
				perror("\nnanosleep");
				exit(1);
			}
		}
	}
	return 0;
}
void overwriteParent(int sig)
{
	if ((sig == 9) || (sig == 19))
	{
		fprintf(stderr,"\n%d:Invalid Argument",sig);
	}
	else
	{
	int status;
	fprintf(stderr,"\nSignal %d recieved by parent",sig);
	kill(pid,SIGKILL);
	wait(&status);
	fprintf(stderr,"\nParent will exit now\n");
	exit(1);
	}
}
void overwriteChild(int sig)
{
	fprintf(stderr,"\nSignal %d recieved by child",sig);
}

	
