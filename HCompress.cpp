#include <iostream.h>
#include "HCompress.h"
//#include "HuffmanTreeNode.h"


int main()
{
	char psource[200] = "d:\\\\in.txt",phuff[200] = "D:\\\\out.huff";
	HCompress huffman(psource,phuff);
	huffman.Compress();
	return 0;
}

