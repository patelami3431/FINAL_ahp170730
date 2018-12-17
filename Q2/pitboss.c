#include <stdio.h>
#include<fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

struct data
{
	
	int per;
	int num_of_trials;
	float success;
	float failure;
};

int main(int argc, char *argv[])
{
	char* filename;
	filename=argv[3];
	FILE *ptr;
	int p; // to store the percentage value
	p = atoi(argv[2]);
	int didnt_get =1;
	if ((p<0) || (p>100))
	{
		fprintf(stderr,"Invalid percentage!");
		exit(1);
	}
	int record_num = 0;
	float srate;
	int trials;
	struct data results;
	ptr=fopen(filename,"rb");
	if (!ptr)
	{
		fprintf(stderr,"Error while opening the file!");
		exit(1);
	}
	unsigned long long offset;
	printf("\nReading results from %s ...\n",filename);
	offset= (record_num - 1) * (sizeof(results));
	fseek(ptr,0,SEEK_SET);
	while(didnt_get)
	{
		fread(&results,sizeof(results),1,ptr);
		if (results.per == p)
			didnt_get = 0;
		record_num++;
	}
	offset= (record_num - 1) * (sizeof(results));
	fseek(ptr,offset,SEEK_CUR);
	printf("\nChecking results for -p = %d ...\n",p);
	printf("Found %d trials.\n",results.num_of_trials);
	printf("\nSuccess: %0.1f%%\n",results.success);
	printf("Failure: %0.1f%%\n",results.failure);
	fclose(ptr);
	return 0;
}
