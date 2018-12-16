#include<time.h>
#include<stdio.h>
#include<stdlib.h>
int main()
{
	time_t start,end;
	double elapsed;
	start=time(NULL);
	int stop=0;
	while(!stop)
	{
		end=time(NULL);
		elapsed=difftime(end,start);
		if (elapsed >=100.0)
			stop=1;
		else
		{
			
