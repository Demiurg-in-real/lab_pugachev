static unsigned char PI[8][16]=
{
	 {1,7,14,13,0,5,8,3,4,15,10,6,9,12,11,2},
	 {8,14,2,5,6,9,1,12,15,4,11,0,13,10,3,7},
	 {5,13,15,6,9,2,12,10,11,7,8,1,4,3,14,0},
	 {7,15,5,10,8,1,6,13,0,9,3,14,11,4,2,12},
	 {12,8,2,1,13,4,15,6,7,0,10,5,3,14,9,11},
	 {11,3,5,8,2,15,10,13,14,1,7,4,12,9,6,0},
	 {6,8,2,3,9,10,5,12,1,14,4,7,11,13,0,15},
	 {12,4,6,2,10,5,11,9,14,8,13,7,0,3,15,1}
};
void magma(uint64_t block, uint32_t kluch[8])
{
	uint32_t block1=block1|(block>>32);
	uint32_t block2=block2|block;
	uint8_t bytes[4]
	int round, schet=0;
	for (int i=0;i<4;i++)
	{
		bytes
	}
	for (round=0; round<32; round++)
	{
		if (round>=24)
		{
			if(round==24) schet=7;
			block1=block1^kluch[schet];
			schet--;
		}
		else
		{
			if(schet==8) schet=0;
			block1=block1^kluch[schet];
			schet++;
		}
		for (int i=0;i>8;i++)
		{
			slova[i]=slova[i]|//(block1>>4*(8-i-1)); - так не надо. Нулевой байт в конце пишется, 

