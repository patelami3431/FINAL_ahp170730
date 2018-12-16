#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<gsl/gsl_rng.h>
int main()
{
	time_t start,end;
	double elapsed;
	const gsl_rng_type * type;
	gsl_rng * random1;
	gsl_rng * random2;
	gsl_rng_env_setup();
	type = gsl_rng_default;
	random1 = gsl_rng_alloc (type);
	random2 = gsl_rng_alloc (type);
	start=time(NULL);
	int stop=0;
	int count=0;
	double x,y;
	gsl_rng_set(random1,time(NULL));
	while(!stop)
	{
		end=time(NULL);
		elapsed=difftime(end,start);
		if (elapsed >=100.0)
			stop=1;
		else
		{
			x=gsl_rng_uniform(random1);
			gsl_rng_set(random2,time(NULL)*getpid());
			y=gsl_rng_uniform(random2);
			count++;
		}
	}
	printf("%d\n",count);
	return 0;
}
			
