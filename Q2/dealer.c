#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<ctype.h>
#include<string.h>

struct data{
	int num_of_trials;;
	float success;
	float failure;
	};

int main(int argc, char *argv[])
{
	if(argc != 6)
	{
		fprintf(stderr, "Not enough arguments! Try again..\n");
		fprintf(stderr,"ERROR 401: Arguments not of the form: ./dealer [-p] [value] [-o] [filename] [int value]\n");
		exit(1);
	}
		
	int opt;
	int i;
	int w;
	char *filename;
	filename = argv[4];
	float srate;//success
	float frate;//failure
	int p = atoi(argv[2]); //to find the value of the percentage
	int trials;
	int scount=0;
	int status;
	pid_t mypid;
	trials  = atoi(argv[5]);
	
	if(!((p>=0) && (p<=100)))
	{
		fprintf(stderr,"Invalid Percentage! Try again..");
		exit(1);
	}

	char *Argv[] = {"./hand","-p", argv[2], NULL};
	while ((opt = getopt(argc,argv,"p:o:")) != -1)
	{
		switch(opt)
		{
			case 'p':
			{
				for (i=0;i<trials;i++)
				{
					pid_t pid;
					if ((pid=fork()) == 0)
					{
						execv("./hand",Argv);
						exit(127);
					}
					else if (pid<0)
					{
						printf("Oops, didn't fork! Try again..\n");
						exit(1);
					}
					sleep(1);
						if (waitpid(pid, &status,0)>0)
						{
						if (WIFEXITED(status) && WEXITSTATUS(status))
						{
						wait(&status);
						if (WEXITSTATUS(status) == 127)
						{
							printf("Oops, exec failed! Try again.. (Check the env variables!)\n");
							exit(1);
						}
						else
						{
							if ((w=WEXITSTATUS(status)) !=  atoi("2"))
								scount++;
							else;
						}
						}
						}
				}
				break;
			}
			case 'o':
			{
				FILE *ptr;
				struct data results;
				ptr=fopen(filename,"ab");
				if (!ptr)
				{
					printf("Unable to open file!");
					return 1;
				}
				srate = ((float)scount/trials)*100.0;
				results.num_of_trials=trials;
				results.success=srate;
				frate= 100.0 -  srate;
				results.failure=frate;
				fwrite(&results, sizeof(struct data), 1, ptr);
				fclose(ptr);
				break;
			}

			default:
				fprintf(stderr, "ERROR 401: Arguments not of the form: ./dealer [-p] [value] [-o] [filename] [int value]]\n");
				exit(1);
		}
	}
			printf ("Created %d processes.\n", trials);
			printf("Success:%.2f%%\n",srate);
			printf("Failure:%.2f%%\n",frate);
			printf("\nResults were written to %s\n", filename);
			return 0;

}

