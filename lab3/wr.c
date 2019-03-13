#include<stdio.h>
int main()
{
	FILE *next;
	//int centr;
	next=fopen("white.txt", "wb+");
	if(next==NULL)
	{
		printf("Error!");
		return 0;
	}
	for(int i=0; i<3000; i++)
	{
		fwrite(&i,sizeof(int), 1, next);
	}
	fclose(next);
	return 0;
}
