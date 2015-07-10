#include <iostream.h>
#include <stdio.h>
unsigned char probe[9];
#include "HDeCompress.h"

int main()
{
	int i;
	probe[1] = 0x80;
	for(i = 2;i <= 8;i ++)
		probe[i] = probe[i-1] >> 1;


	char psource[200] = "d:\\\\in.txt",phuff[200] = "D:\\\\out.huff";
	HDeCompress huffman(psource,phuff);
	huffman.DeCompress();
	return 0;
}

