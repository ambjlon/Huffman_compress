#ifndef HUFF_DECOMPRESS
#define HUFF_DECOMPRESS
#include <iostream>
#include <limits.h>
#include <time.h>
#include <stdio.h>
using namespace std;
#include "HuffmanTreeNode.h"

class HDeCompress
{
public:
	FILE *source;//the source file;
	FILE *dst;//the huffman file;
	const char *sourcefilename,*dstfilename;
	HNode *HTree;//从文件读入huffman树，放在这个数组中
	int nodenum;//叶子节点
	unsigned char numint;//!
	long int totalbits;//the total number of the bits
	char only_one_char;
	unsigned char only_c;//只有一个字符时用这个变量来记录它
	clock_t start,finish;
	CHeoilDlg *InerDlg;
	
	HDeCompress(const char *psource,const char *phuff,CHeoilDlg *Dlg);
	~HDeCompress();
	void ReadyData();//read the file for the first time and iniate the huffmanree
	void DeCode();
	void DeCompress();
};
HDeCompress::HDeCompress(const char *psource,const char *phuff,CHeoilDlg *Dlg)
{
	sourcefilename = psource;
    dstfilename = phuff;
	nodenum = 0;
	totalbits = 0;
	only_one_char = 0;
	HTree = NULL;
	numint = 0;//!
	start = 0;
	finish = 0;
	InerDlg = Dlg;
}
HDeCompress::~HDeCompress()
{
	delete []HTree;
}
void HDeCompress::ReadyData()
{
	unsigned char i;

	source = fopen(sourcefilename,"rb+");
	fread(& i,1,1,source);
	fseek(source,i + 1,0);

	fread(& only_one_char,1,1,source);
	if(only_one_char)
	{
		fread(& totalbits,4,1,source);
		fread(& only_c,1,1,source);
	}
	else
	{
	fread(& numint,1,1,source);
	fread(& totalbits,4,1,source);
	fread(& nodenum,4,1,source);
	HTree = new HNode[nodenum];
	fread(HTree,sizeof(HNode),nodenum,source);
	}
	if(InerDlg->m_check)
	InerDlg->MyCtrl.SetPos(1);
//	fclose(huff);
}
void HDeCompress::DeCode()
{
	int i;
	int ccc = 1;
	
	unsigned char probe[9];
	if(! only_one_char)
	{
		probe[1] = 0x80;
		for(i = 2;i <= 8;i ++)
			probe[i] = probe[i-1] >> 1;
		
		int j,p;
		long int tb;
		//unsigned char tmp;
		unsigned long int counter,cct;
		char bit;
		unsigned char c;
		
		tb = totalbits;
		totalbits = LONG_MAX;
		//huff = fopen("D:\\in.huff","rb");
		dst = fopen(dstfilename,"wb");
		//fseek(huff,9 + nodenum*sizeof(HNode),0);
		p = 0;
		counter = 0;
		for(j = 0;j < numint + 1;j ++)
		{
			if(j != numint)
			{
				cct = 0;
				while(1)
				{
					fread(& c,1,1,source);
					cct += 8;
					if(InerDlg->m_check)
					InerDlg->MyCtrl.SetPos(ccc + ((float)cct / LONG_MAX) * (100 / (numint + 1)));
					for(bit = 1;bit <= 8;bit ++,counter ++)
						if((probe[bit] & c) == probe[bit])//bit位是1
						{
							p = HTree[p].right;
							if(HTree[p].left == -1)
							{
								fwrite(& HTree[p].right,1,1,dst);
								p = 0;//bit一定要译完
							}
						}
						else
						{
							p = HTree[p].left;
							if(HTree[p].left == -1)
							{
								fwrite(& HTree[p].right,1,1,dst);
								p = 0;//bit一定要译完
							}
						}
						if(counter == totalbits)
						{
							counter = 0;
							break;
						}
						if(counter > totalbits)
						{
							counter = counter - totalbits;
							break;
						}
				}
				ccc +=  (100 / (numint + 1));
			}
			else
			{
				totalbits = tb;
				cct = 0;
				while(1)
				{
					c = 0;
					fread(& c,1,1,source);
					cct += 8;
					if(InerDlg->m_check)
					InerDlg->MyCtrl.SetPos(ccc + ((float)cct / totalbits) * (100 / (numint + 1)));
					for(bit = 1;bit <= 8 && counter < totalbits;bit ++,counter ++)
						if((probe[bit] & c) == probe[bit])//bit位是1
						{
							p = HTree[p].right;
							if(HTree[p].left == -1)
							{
								fwrite(& HTree[p].right,1,1,dst);
								p = 0;//bit一定要译完
							}
						}
						else
						{
							p = HTree[p].left;
							if(HTree[p].left == -1)
							{
								fwrite(& HTree[p].right,1,1,dst);
								p = 0;//bit一定要译完
							}
						}
						if(counter == totalbits)
							break;
				}
			}
		}
	}
	else
	{
		dst = fopen(dstfilename,"wb");
		for(i = 1;i <= totalbits;i ++)
			fwrite(& only_c,1,1,dst);
		if(InerDlg->m_check)
		InerDlg->MyCtrl.SetPos(100);
	}
	fclose(dst);
	fclose(source);
	if(InerDlg->m_check)
	InerDlg->MyCtrl.SetPos(100);
}
void HDeCompress::DeCompress()
{
	start = clock();
	ReadyData();
	DeCode();
	finish = clock();
	InerDlg->m_Time = ((double)(finish - start)) / CLOCKS_PER_SEC;
}
#endif

