#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/mman.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<stdint.h>
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
	uint64_t startLBA;
	uint64_t endLBA;
	uint32_t attributes[2];
	uint32_t typeofRazd[18];
}__attribute__((packed));

void format_MBR();//done
void format_GPT();//done
uint32_t crc32();//done
void format_razdel();//done
uint32_t  guid();//done
void zapis();//done
void 
//void right_swap(char *file1, char *file2);
int main(int argc, char* argv[])
{
	return 0;
}
void format_MBR(uct form_MBR *mbr)
{
	mbr->activ_nach_cil=0x00020000;
	mbr->type_be_end=0xffffffee;
	mbr->absoluteLBA=0x00000001;
	mbr->size_sectors=(razmer/512-1); //вроде верно
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
	gpt->Alternatelba=(razmer/512-1);
	gpt->Firstusablelba=0x800;
	gpt->Lastusablelba=(razmer/512-33);
	gpt->Partitionlba[0]=0x00000002;
	gpt->Partitionlba[1]=0x00000000;
	gpt->numberofpartent=0x00000080;
	gpt->sizeofpart=0x00000080;
	for(int i=0; i<105;i++)
	{
		gpt->reserved2[i]=0x00000000;
	}
	for(int i=0;i<4; i++)
	{
		guid(nas);
		gpt->uniqueGUID[i]=nas;
	}
}
void format_razdel(struct razdel raz)
{
	raz->typeGUID[0]=0xc12a7328;
	raz->typeGUID[1]=0x11d2f81f;
	raz->typeGUID[2]=0xa0004bba;
	raz->typeGUID[3]=0x3bc93ec9;
	uint32_t smesh;
	for(int i=0; i<4; i++)
	{
		guid(smesh);
		raz->uniqueGUID[i]=smesh;
	}
	raz->startlba=nachalo; //!!!
	raz->endlba=konec;
	raz->attributes[0]=0x00;
	raz->attributes[1]=0x00;
	for (int i=0;i<18;i++)
	{
		raz->typeofrazd[i]=array1[i];
	}

}
void guid()
{
	srand((uint32_t)time(NULL));
	uint32_t generate=randint();
	return generate;
}

unsigned int crc32b(unsigned char *message) 
{
	int i, j;
	uint32_t byte, crc, mask;
	i = 0;
	crc = 0xFFFFFFFF;
	while (message[i] != 0)
	{
		byte = message[i];           
		crc = crc ^ byte;
		for (j = 7; j >= 0; j--)
		{
			mask = -(crc & 1);
			crc = (crc >> 1) ^ (0xEDB88320 & mask);
		}
		i= i + 1;
	}
	return ~crc;
}
void zapis()//so schetom dovedi do uma
{
	uint32_t *ptr1,*ptr2; int openf,schet=0x1be; struct stat st;
	openf=open(file,O_RDWR);
	fstat(openf,&st);
	ptr1=(uint32_t*)mmap(NULL, st.st_size,PROT_READ|PROT_WRITE, MAP_SHARED, openf,0);
	ptr2=(uint64_t*)mmap(NULL, st.st_size, PROT_READ|PROT_WRITE, MAP_SHARED,openf,0);
	*((uint32_t*)(ptr1+schet))=Mbr->aktiv_nach_cil;
	*((uint32_t*)(ptr1+schet+4))=Mbr->type_be_end;
	*((uint32_t*)(ptr1+schet+8))=Mbr->absolute_LBA;
	*((uint32_t*)(ptr1+schet+12))=Mbr->size_sectors;
	schet=512;
	*((uint32_t*)(ptr1+schet-2))=0xaa55;
	*((uint32_t*)(ptr1+schet))=Gpt->signature[0];
	*((uint32_t*)(ptr1+schet+4))=Gpt->signature[1];
	*((uint32_t*)(ptr1+schet+8))=Gpt->zagolovok;
	*((uint32_t*)(ptr1+schet+12))=Gpt->size_zagolovok;
	*((uint32_t*)(ptr1+schet+20))=Gpt->reserved;
	*((uint32_t*)(ptr1+schet+24))=Gpt->Mylba[0];
	*((uint32_t*)(ptr1+schet+28))=Gpt->Mylba[1];
	*((uint64_t*)(ptr2+schet+32))=Gpt->Alternallba;
	*((uint64_t*)(ptr2+schet+40))=Gpt->Firstusablelba;
	*((uint64_t*)(ptr2+schet+48))=Gpt->Lastusablelba;
	//*((uint32_t*)(ptr1+schet))=Gpt->
	schet+=56;
	for(int i=0;i<4;i++)
	{
		*((uint32_t*)(ptr1+schet))=Gpt->DiskGUID[i];
		schet+=4;
	}
	*((uint32_t*)(ptr1+schet))=Gpt->Partitionlba[0];
	*((uint32_t*)(ptr1+schet+4))=Gpt->Partitionlba[1];
	*((uint32_t*)(ptr1+schet+8))=Gpt->numberofpart;
	*((uint32_t*)(ptr1+schet+12))=Gpt->sizeofpart;
	schet+=16;
	for (int i=0; i<105;i++)
	{
		*((uint32_t*)(ptr1+schet))=Gpt->reserved2[i];
		schet+=4;
	}
	for (int i=0;i<number; i++)
	{
		Razmer=(razmer/512)/number;
		razmer1=2048+(Razmer+1)*i;
		razmer2=2048+Razmer*(i+1);
		format_razdel(razmer1,razmer2);	
		for(int y=0;y<4;y++)
		{
			*((uint32_t*)(ptr1+schet))=Raz->typeGUID[i];
			*((uint32_t*)(ptr1+schet+16))=Raz->UniqueGUID[i];
			schet+=4;
		}
		*((uint64_t*)(ptr2+schet))=Raz->startLBA;
		schet+=8;
		*((uint64_t*)(ptr2+schet))=Raz->endLBA;
		schet+=8;
		*((uint32_t*)(ptr1+schet))=Raz->attributes[0];
		schet+=4
		*((uint32_t*)(ptr1+schet))=Raz->attributes[1];
		schet+=4
		for(int y=0;y<18;y++)
		{
			*((uint32_t*)(ptr1+schet))=Raz->typerazd[i];
			schet+=4;
		}
	}
	munmap(ptr1,st.st_size);
	munmap(ptr2,st.st_size);
	close(openf);
	read();
	del(openf);
	FILE *openf=fopen(file, "rb+");
	if(opnef==NULL)
	{
		printf("Daleko zashol, no poshol nahui");
		return 0;
	}
	unsigned int *wr;
	fseek(openf,512,SEEK_SET);
	for (int y=0; y<512; y++)
	{
		wr=gptmas[y];
		fwrite(&wr, sizeof(uint32_t),1,openf);
	}
	for (int i=0; i<number;i++)
	{
		for (int y=0; y<128; y++)
		{
			wr=massive[i][y];
			fwrite(&wr, sizeof(uint32_t),1,openf);
		}
	}
	fseek(openf, -33*512, SEEK_END);
	for(int i=0; i<number;i++)
	{
		for(int y=0; y<128; y++)
		{
			wr=massive[i][y];
			fwrite(&wr, sizeof(uint32_t),1,openf);
		}
	}
	fseek(openf, -512,SEEK_END);
	for(int i=0; i<512;i++)
	{
		wr=gptmas[i];
		fwrite(&gptmas,sizeof(uint32_t),1,openf);
	}
	return 0;
}
int reaD()
{
	FILE *openf=fopen(file1, "rb+");uint32_t *chit, numb1=0, massive[number][128];
	if(openf==NULL)
	{
		printf("Pshol nah");
		return 0;
	}
	fseek(openf,512, SEEK_SET);
	for (int i=0;i<number;i++)
	{
		if(shelk)
		{
			for (int y=0;y<512;y++)
			{
				gptstr[y]=fread(&chit,sizeof(uint32_t), 1, openf);
			}
			shelk=false;
		}
		for (int y=0; y<128/4)
		{
			massive[i][y]=fread(&chit, sizof(uint32_t),1,openf);
		}
	}
//ne hvataet рассчёта crc32 и дозаписи в конце (ну это уже через fopen сделаю, хер ли мудачиться просто такё

	gptstr[некоторое]=uint32_t crc32(massive);
	gptstr[некот]=uint32_t crc3w(gptstr);
	return gptstr, massive;
}


