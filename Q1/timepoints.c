#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
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
	double sq_x, sq_y, sum;
	double sqroot;
	double pi,deviation;
	double error;
	int count=0;
	int points=0;	//to count the points in circle
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
			sq_x=x*x;
			sq_y=y*y;			
			sum=sq_x+sq_y;
			sqroot=sqrt(sum);
			if ( sqroot < 1.0)
				points++;
			count++;
		}
	}
	pi=((double)count/(double)count)*4.0;
	printf("Estimated value = %0.4f\n",pi);
	deviation = pi-(22.0/7.0);
	printf("Deviation = %0.4f\n",deviation);
	error=(deviation * 7.0 * 100.0)/22.0;
	printf("Error = %0.4f%%\n",fabs(error));
	printf("The number of points is %d\n",count);
	return 0;
}
			
