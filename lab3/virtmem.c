#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
int main(int argc, char* argv[])
{
	int sd; struct stat st; char *ptr;
	sd=open(argv[1], O_RDONLY);
	fstat(sd, &st);
	ptr=(char*)mmap(NULL,st.st_size, PROT_READ, MAP_PRIVATE,sd,0); //pochitai pro virtualnuu pamat, a to tak ne sovsem ponyatno s hodu... Mdeeee... Ti tupoi, Andrei
	printf("%04x\n", *((unsigned short*)(ptr+510)));
	munmap(ptr, st.st_size);
	close(sd);
	return 0;
}

