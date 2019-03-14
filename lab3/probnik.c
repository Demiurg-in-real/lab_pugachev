#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include <stdbool.h>
int main(int argc, char* argv[])
{
	int sd, i=0; struct stat st; char *ptr, *ptr1;
	sd=open(argv[1], O_RDWR);
	int schet=0;
	bool shelk=false;
	fstat(sd, &st);
	//for(i=0; i<1048575; i++)
	//{
	ptr=(char*)mmap(NULL,st.st_size, PROT_READ, MAP_PRIVATE,sd,0);	//pochitai pro virtualnuu pamat, a to tak ne sovsem ponyatno s hodu... Mdeeee... Ti tupoi, Andrei
	ptr1=(char*)mmap(NULL, st.st_size, PROT_WRITE, MAP_SHARED, sd,0);
	for (i=0; i<1048575; i++)
	{
		if(i==510)
		{
			printf("cto za...");
		}
		if (*((unsigned short*)(ptr+i))==*((unsigned short*)(ptr+510)))
		{
			shelk=true;
			printf("%i", i);
		}

		//if (shelk)
		//{
		//	printf("1")
		//}

		//printf("%04x", *((unsigned short*)(ptr+i)));
		schet++;
		if (schet==16)
		{
			schet=0;
			//printf("\n");
		}
	}
	munmap(ptr, st.st_size);
	close(sd);
	return 0;
}

