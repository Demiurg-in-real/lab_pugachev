#include<stdio.h>
#include<stdint.h>
int main()
{
	uint8_t a=0x0,b=0x0;
	uint16_t c=0xaafe;
	a=a|c;
	b=b|(c>>4);
	printf("a=%04X; b=%04X; c=%04X;\n",a,b,c);
	return 0;
}
