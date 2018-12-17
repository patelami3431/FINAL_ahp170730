#include<stdio.h>
#include <gsl/gsl_rng.h>
#include <time.h>
#include<math.h>
#include<stdlib.h>
int main(int argc, char *argv[])
{
	int count=0;
	int i=0;
	int trials=atoi(argv[1]);
	double x;
	double y;
	double sq_x, sq_y, sum;
	double sqroot;
	double pi,deviation;
	double error;
	const gsl_rng_type * type;
	gsl_rng * random1;
	gsl_rng * random2;
	gsl_rng_env_setup();
	type = gsl_rng_default;
	random1 = gsl_rng_alloc (type);
	random2 = gsl_rng_alloc (type);
	if (random1 == NULL)
	{
		fprintf(stderr, "\nNot enough space to allocate in the memory\n");
		exit(1);
	}
	gsl_rng_set(random1,time(NULL));
	while(i<trials)
	{
        	x=gsl_rng_uniform(random1);
		gsl_rng_set(random2,time(NULL)*getpid());
	        y=gsl_rng_uniform(random2);
		sq_x=x*x;
		sq_y=y*y;			
		sum=sq_x+sq_y;
		sqroot=sqrt(sum);
		if ( sqroot < 1.0)
			count++;
		i++;
	}
	//double ratio = (double)count/(double)trials;

	pi=((double)count/(double)trials)*4.0;
	printf("Estimated value = %0.4f\n",pi);
	deviation=pi-(22.0/7.0);
	printf("Deviation = %0.4f\n",deviation);
	error=(deviation * 7.0 * 100.0)/22.0;
	printf("Error = %0.4f%%\n",fabs(error));
	//printf("x=%0.4f",x);
	//printf("sqroot=%0.4f",sqroot);
	gsl_rng_free (random1);
	gsl_rng_free (random2);
	return 0;
}
													                           
