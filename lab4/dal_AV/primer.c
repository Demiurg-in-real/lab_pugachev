#include <stdint.h>

//vstavil

#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include <stdbool.h>
#include<stdlib.h>

//vstavil
uint_least32_t Crc32(unsigned char *buf, size_t len);
int razmer(int chislo, char argum);
struct part {
	uint8_t boot; //unsigned int - more universal
	uint8_t chs[3];
	uint8_t type;
	uint8_t chs2[3];
	uint8_t LBA;
	uint8_t size;//System 5-  рассказывается, как компилятор должен собирать сишный код. Под винду есть заморочка с упаковкой структур (для того, чтобы память корректно занимало. __attribute__((packed)); - атрибут для того, чтобы эту структуру компилятор "упаковал" корректно. Пишется после скобки структуры
};
struct mbr {
	uint8_t code[446];
	struct part P[4];
	uint8_t sig[];
}__attribute__((packed));
struct mbr *mbr;
mbr=(struct mbr*) ptr;
mbr->(sig[0]=0xaa);
mbr->sig[1]=0x55;
mbr->P[0].type=0xee
mbr->P[0].lba=1;
//mbr->P[0].size=st.st_size/512-1;
mbr->P[0].chs[0]=0xFF;
mbr->P[0].chs[1]=0xFF;
mbr->P[0].chs[2]=0xFF;


//struct gpt {
	



int main(int argc, char* argv[])
{
	int razm;
	razm=razmer(razm, argv[1]);
	int sd, i=0; struct stat st; short int *ptr;
	sd=open(argv[1], O_RDWR);
	fstat(sd,&st);
	ptr=(unsigned short*)mmap(NULL, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, sd, 0);
	munmap(ptr, st.st_size);
	close(sd);
	return 0;
}

int razmer(int chislo, char argum)
{
	FILE *magad=fopen(argum, "rb");
	if (magad==NULL)
	{
		printf("Something went wrong, check the code, pls");
		return -555;
	}
	fseek(magad, 0, SEEK_END);
	chislo=ftell(magad);
	fclose(magad);
	return chislo;
}
uint_least32_t Crc32(unsigned char *buf, size_t len)
{
	    uint_least32_t crc_table[256];
	        uint_least32_t crc; int i, j;

		    for (i = 0; i < 256; i++)
			        {
					        crc = i;
						        for (j = 0; j < 8; j++)
								            crc = crc & 1 ? (crc >> 1) ^ 0xEDB88320UL : crc >> 1;

							        crc_table[i] = crc;
								    };

		        crc = 0xFFFFFFFFUL;

			    while (len--)
				            crc = crc_table[(crc ^ *buf++) & 0xFF] ^ (crc >> 8);

			        return crc ^ 0xFFFFFFFFUL;
}
