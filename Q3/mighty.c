#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Invalid arguments!");
		fprintf(stderr,"Arguments should be of the form: ./mighty [filename] [filename]");
		exit(1);
	}
	char *infile;
	int status;
	char *outfile;
	infile = argv[1];
	int p[2];
	FILE *ptr;
	FILE *ptr1;
	int c;	//characters to be read from the file
	//c = (char *) malloc (100*sizeof(char));
	outfile = argv[2];
	pid_t pid;
	if (pipe(p) == -1)
	{
		fprintf(stderr,"Problem with pipe!");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		fprintf(stderr,"Didn't fork!");
		exit(1);
	}
	else if(pid == 0)
	{
		//in child
		close(p[1]);
		dup2(p[0],0);
		char *arg[]= {"/usr/bin/cat","/usr/bin/cat","-b",infile,NULL};
		execl(arg[0],arg[1],arg[2],arg[3],arg[4]);
		close(p[0]);
	}
	else
	{
		//in parent
		close(p[0]);
		dup2(p[1],1);
		close(p[1]);
		ptr1 = fopen(infile,"r");
		if (!ptr1 )
		{
			fprintf(stderr,"Error!");
			exit(1);
		}
		if(!(ptr= fopen(outfile,"w")))
		{
			fprintf(stderr,"Error!");
			exit(1);
		}

		while((c=fgetc(ptr1))!= EOF ){
		fprintf(stdout,"%c", c);
		fputc(c,ptr);
		}
		fclose(ptr);
		fclose(ptr1);
		wait(&status);
	}
	return 0;
}

