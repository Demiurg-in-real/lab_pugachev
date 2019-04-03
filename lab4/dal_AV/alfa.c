#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdint.h>
//#include<io.h>
struct form_MBR
{
	uint32_t aktiv_nach_cil;
	uint32_t type_be_end;
	uint32_t absolute_LBA;
	uint32_t size_sectors;
}__attribute__((packed));
//в число секторов в лба в конце защитного мбр пишется (кол-во секторов на самом файле-1)
//(type_be_end - номер головки диска на которой заканчивается раздел и номер цилиндра и сектора, на котором заканчивается раздел - можно записать =0x00 все
struct GPT
{
	uint32_t signature[2];
	uint32_t zagolovok;
	uint32_t size_zagolovok;
	uint32_t All_crc32;
	uint32_t reserved;
	uint32_t Mylba[2];
	uint64_t Alternatelba;
	uint64_t Firstusablelba;
	uint64_t Lastusablelba;
	uint32_t DiskGUID[4];
	uint32_t Partitionlba[2];
	uint32_t numberofpartent;
	uint32_t sizeofpart;
	uint32_t Partitioncrc32[2];
	uint32_t reserved2[105];
} __attribute__((packed));
struct razdel
{
	uint32_t typeGUID[4];
	uint32_t uniqueGUID[4];
	uint32_t startLBA[2];
	uint32_t endLBA[2];
	uint32_t attributes[2];
	uint32_t typeofRazd[18];
}__attribute__((packed));

void format_MBR();
void format_GPT();
void crc32();
void format_razdel();
uint32_t  guid();
void zapis();
//void right_swap(char *file1, char *file2);
int main(int argc, char* argv[])
{
	return 0;
}
void format_MBR(struct form_MBR *mbr)
{
	mbr->activ_nach_cil=0x00020000;
	mbr->type_be_end=0x000000ee;
	mbr->absoluteLBA=0x00000001;
	mbr->size_sectors //дома допридумать
}
void format_GPT(struct GPT gpt)
{
	gpt->signature[1]=0x54524150;
	gpt->signature[0]=0x20494645;
	gpt->zagolovok=0x00010000;
	gpt->size_zagolovok=0x0000005c;
	gpt->reserved=0x00000000;
	gpt->Mylba[0]=0x00000001;
	gpt->Mylba[1]=0x00000000;
	gpt->Alternatelba=;
	gpt->Firstusablelba=;
	gpt->Lastusablelba=;
	gpt->Partitionlba[0]=0x00000002;
	gpt->Partitionlba[1]=0x00000000;
	gpt->numberofpartent=0x00000080;
	gpt->sizeofpart=0x00000080;
	for(int i=0; i<105;i++)
	{
		gpt->reserved2[i]=0x00000000;
	}
}
void format_razdel(struct razdel raz)
{
	raz->typeGUID[0]=;
	raz->typeGUID[1]=;
	raz->typeGUID[2]=;
	raz->typeGUID[3]=;
	uint32_t smesh;
	for(int i=0; i<4; i++)
	{
		guid(smesh);
		raz->uniqueGUID[i]=smesh;
	}

}	
/*void right_swap(char *file1, char *file2)
{
	int x,y,z,schet=0,const1=1024, value=const1,openf;
	unsigned char *ptr, pixels[1024][1024][3], a,b,c,d;
	struct stat st;
	openf=open(file1, O_RDONLY);
	fstat(openf, &st);
	ptr=(uint8_t*)mmap(NULL, st.st_size, PROT_READ , MAP_PRIVATE, openf, 0);
	for (x=0;x<1024;x++)
	{
		for (y=0; y<1024;y++)
		{
			for (z=0; z<3;z++)
			{
				pixels[x][y][z]=*((uint8_t*)(ptr+56670+schet));
				schet++;
				//printf("1");
			}
			//printf("2");
		}
		printf("%i\n", schet);
	}// заканчивает цикл и программу тошнит ошибкой сегментирования. Просто хз что делать
	//printf("4");//вот этот момент программа уже не выполняет, заканчивая цикл вылетает с ошибкой
	munmap(ptr, st.st_size);
	close(openf);
	//printf("5");
	for(x=0; x<512; x++)
	{
		for(y=0;y<(const1-1);y++)
		{
			for (z=0;z<3;z++)
			{
				a=pixels[x][y][z];
				b=pixels[y][const1][z];
				c=pixels[const1][value][z];
				d=pixels[value][x][z];
				pixels[x][y][z]=b;
				pixels[y][const1][z]=c;
				pixels[const1][value][z]=d;
				pixels[value][x][z]=a;
			}
		}
	}
	schet=0;
	openf=open(file2, O_WRONLY | O_CREAT, S_IWRITE | S_IREAD);
	fstat(openf, &st);
	ptr=(uint8_t*)mmap(NULL, st.st_size, PROT_WRITE, MAP_SHARED, openf,1);
	for(x=0;x<1024;x++)
	{
		for(y=0;y<1024;y++)
		{
			for(z=0;z<3;z++)
			{
				//a=pixels[x][y][z];
				*((uint8_t*)(ptr+schet))=pixels[x][y][z];
				schet++;
			}
		}
	}
}
