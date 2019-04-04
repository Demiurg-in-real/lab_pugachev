#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include <stdbool.h>
#include<stdlib.h>
#include<stdint.h>
struct zp 
{
	uint64_t adel;
};
//#include<time.h>
int main(int argc, char* argv[])
{
	int sd, i=0; struct stat st; uint64_t *ptr;struct zp *a;
	a->adel=615;
	sd=open(argv[1], O_RDWR);
	fstat(sd, &st);
	ptr=(uint64_t*)mmap(NULL,st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED,sd,0);
	*((uint64_t*)(ptr+0))=a->adel;
	munmap(ptr, st.st_size);
	close(sd);
	return 0;
}

