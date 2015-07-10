#ifndef HUFF_COMPRESS
#define HUFF_COMPRESS
#include <iostream>
#include <stdio.h>
#include <time.h>
//#include <limits.h>
//#include <string>
#include "HuffmanTreeNode.h"
using namespace std ;

#define MAX 512

class HCompress
{
public:
	FILE *source;//the source file;
	FILE *huff;//the huffman file;
	const char *sourcefile,*hufffile;
	HNode_mem HTree[MAX];//memory the huffmantree in memory
	HNode *FHTree;//this dynamic tree is placed in memory EMS memory
	QueryList list[MAX / 2];
	int leafnum;//number of leaves,i.e kinds of bytes.
	unsigned long int content;//for computing how large the source file is.
	unsigned char numint;//when the file is over 256M(about),this nodes the numbers
	long int totalbits;//the total number of the bits.
	char only_one_char;//marked if only one kind of character.
	unsigned char only_c;//note the only char.
	int root;//position of root node.
	clock_t start,finish;;
	CHeoilDlg *InerDlg;
	
	HCompress(const char *psource,const char *phuff,CHeoilDlg *Dlg);
	~HCompress();
	void IniateHTree();
	void BulidHTree();
	void EditCode();
	void BulidFHTree();
	void WriteDisk();
};
HCompress::~HCompress()
{
	delete []FHTree;
}
HCompress::HCompress(const char *psource,const char *phuff,CHeoilDlg *Dlg)
{
	sourcefile = psource;
	hufffile = phuff;
	leafnum = 0;
	content = 0;
	totalbits = 0;
	only_one_char = 0;
	FHTree = NULL;
	root = -1;
	numint = 0;//!
	InerDlg = Dlg;
}	
void HCompress::IniateHTree()
{
    unsigned char c;
    source = fopen(sourcefile,"rb");
	//test time from here
	start = clock();


	//initialize ctrlbar
    InerDlg->MyCtrl.SetRange(0,100);
	if(InerDlg->m_check)
		InerDlg->MyCtrl.SetPos(0);
	//Ended while,we have:
	//the capacity of the source file is content KB
	//and,HTree haved been initialized
	while(fread(& c,1,1,source) == 1)
	{
		content ++;
		if(HTree[c].freq == 0)//hash constrouctor
		{
			leafnum ++;
			//test time
			//finish = clock();
			//InerDlg->m_Time = ((double)(finish - start)) / CLOCKS_PER_SEC;
			//InerDlg->UpdateData(false);//
		}
		HTree[c].freq++;
	}
	only_c = c;
	fclose(source);
}
void HCompress::BulidHTree()
{
	int j;
	int here;
	int min,sec_min;

	//Bulid Huffmantree
	here = 0;
	while(1)
	{
		for(j = 0;j < MAX;j ++)
			if(HTree[j].parent == -2 && HTree[j].freq != 0)
			{
				min = j;
				break;
			}

		for(j = min + 1;j < MAX;j ++)
			if(HTree[j].parent == -2&& HTree[j].freq != 0 && HTree[j].freq <  HTree[min].freq)
				min = j;

		for(j = 0;j < MAX;j ++)
			if(HTree[j].parent == -2 && HTree[j].freq != 0 && min != j)
			{
				sec_min = j;
				break;
			}
		if(j == MAX)
		{
			root = min;
			break;//while循环只能从这里跳出，此时root 就是min
		}
		for(j = sec_min + 1;j < MAX;j ++)
			if(HTree[j].parent == -2&& HTree[j].freq != 0 && j != min && HTree[j].freq <  HTree[sec_min].freq)
				sec_min = j;
		for(j = here; j < MAX;j ++)
			if(HTree[j].freq == 0)
			{
				HTree[j].left = min;
				HTree[j].right = sec_min;
				HTree[min].parent = j;
				HTree[sec_min].parent = j;
				HTree[j].freq = HTree[min].freq + HTree[sec_min].freq;
				break;
			}
		here = j + 1;
	}

	//test time
	//finish = clock();
	//InerDlg->m_Time = ((double)(finish - start)) / CLOCKS_PER_SEC;
	//InerDlg->UpdateData(false);//
	//through the value of here,judge if only one char in file.
	if(here == 0)
	{
		only_one_char = 1;
		totalbits = HTree[only_c].freq;
	}
	if(InerDlg->m_check)
	InerDlg->MyCtrl.SetPos(1);
}
void HCompress::EditCode()
{
	int i;
	if(! only_one_char)
	{
		int j;
	    char code[256];
	    int flag;

	    code[255] = 0;
	    for(i = 0;i < MAX;i ++)
		{
			if(HTree[i].left == -1 && HTree[i].parent != -2)
			{
				flag = 254;
				j = i;
				while(HTree[j].parent != -2)
				{
					if(HTree[HTree[j].parent].left == j)
						code[flag --] = '0';
					else
						code[flag --] = '1';
					j = HTree[j].parent;
				}
				list[i].bits = 254 - flag;//hash ,improve the speed of this program.
		        list[i].s = &code[flag + 1];
			}
		}
	}
	else
		;

	//test time
	//finish = clock();
	//InerDlg->m_Time = ((double)(finish - start)) / CLOCKS_PER_SEC;
	//InerDlg->UpdateData(false);//
}
void HCompress::BulidFHTree()
{
	int quebg,quefns,quetmp;
	FHTree = new HNode[2 * leafnum - 1];

	FHTree[0] = HTree[root];
	quebg = quefns = 0;
	if(! only_one_char)
	{
		while(1)
		{
			quetmp = quefns;
		    while(quebg <= quefns)
			{ 
				if(FHTree[quebg].left != -1)
				{
					if(HTree[FHTree[quebg].left].left == -1)
					{
						FHTree[++ quetmp].right = FHTree[quebg].left;
					    FHTree[quetmp].left = -1;
					    FHTree[quebg].left = quetmp;
					}
					else
					{
						FHTree[++ quetmp] = HTree[FHTree[quebg].left];
						FHTree[quebg].left = quetmp;
					}


					if(HTree[FHTree[quebg].right].left == -1)
					{
						FHTree[++ quetmp].right = FHTree[quebg].right;
					    FHTree[quetmp].left = -1;
					    FHTree[quebg].right = quetmp;
					}
					else
					{
						FHTree[++ quetmp] = HTree[FHTree[quebg].right];
					    FHTree[quebg].right = quetmp;
					}
				}
				quebg ++;
			}
			if(quetmp == quefns)
				break;
			quebg = quefns + 1;
			quefns = quetmp;
		}
	}
	else
		;
	//test time
	//finish = clock();
	//InerDlg->m_Time = ((double)(finish - start)) / CLOCKS_PER_SEC;
	//InerDlg->UpdateData(false);//
	if(InerDlg->m_check)
	InerDlg->MyCtrl.SetPos(3);
}
void HCompress::WriteDisk()
{
	unsigned char i;
	huff = fopen(hufffile,"rb+");
	source = fopen(sourcefile,"rb");
	fread(& i,1,1,huff);

	if(! only_one_char)
	{
		int j,k,t,m,q;
		unsigned long int cct = 0;
	    unsigned char c;
	    unsigned char bitset;//write this number to disk
	    char vector[256];//read bits from here with pace of 8,change it to unsign char
	    int flag,bits;


	    //文件中的一个字节标志是不是只有一种字符，接着的四个字节是totalbits，
		//然后是haffman树的节点数，占4字节
	    //然后是一个哈弗曼树的存储，最后是比特流.因此先将huff 文件指针后移
	    //9 + (2 * leafnum - 1)*sizeof(HNode) 个字节.
	    fseek(huff,i + 1 + 10 + (2 * leafnum - 1)*sizeof(HNode),0);//!
	    k = 0;
		flag = 0;
	    while(1)
		{
			
	        bits = 0;
	        //last time,are characters left?
	        if(flag)
			{
				for(j = 0;k < list[c].bits;k ++,j ++)
					vector[j] = list[c].s[k];
		        bits = j;
			}
			flag = 0;
		    //有两种方式跳出这个while 循环：
		    //1.fread(& c,1,1,source) == 1不成立.那么flag == 0；
		    //2.从else 中的break 跳出，那么flag == 1；
   	        while(fread(& c,1,1,source) == 1)
			{
				cct ++;
				//display gurage
				if(InerDlg->m_check)
				InerDlg->MyCtrl.SetPos(3 + ((float)cct / content) * 97);
				//应用哈希散列表，查找C的位置这一操作省掉了！
		        if(bits + list[c].bits <= 256)
				{
					for(j = bits,k = 0;j < bits + list[c].bits;j ++,k ++)
						vector[j] = list[c].s[k];
					bits = bits + list[c].bits;
				}
			    else
				{
					for(j = bits,k = 0;j < 256;j ++,k ++)
						vector[j] = list[c].s[k];
				    bits = 256;
				    flag = 1;
				    break;
				} 
			}

			//totalbits += bits;
			if(totalbits + bits < totalbits)//!
			{//!
				numint ++;//!
				totalbits = bits - (LONG_MAX - totalbits);//!
			}//!
			else//!
				totalbits += bits;//!


			
			for(j = 0;j < bits;j += 8)
			{
				bitset = 0;
	
				for(t = j,m = 7;t < j + 8 && t < bits;t ++,m --)//!!!!!!!!jjj
				if(vector[t] == '1')
					bitset = bitset + 1 * (1 << m);
				else
					bitset = bitset + 0 * (1 << m);
				fwrite(& bitset,1,1,huff);
			}
			if(flag == 0)
				break;


			//test time
	       finish = clock();
	       InerDlg->m_Time = ((double)(finish - start)) / CLOCKS_PER_SEC;
		}
		//比特流已经写完，在写译码时必要的信息
		fseek(huff,i + 1,0);
	    fwrite(& only_one_char,1,1,huff);
		fwrite(& numint,1,1,huff);//!
	    fwrite(& totalbits,4,1,huff);
		q = (2 * leafnum - 1);
		fwrite(& q,4,1,huff);
	    fwrite(FHTree,sizeof(HNode),(2 * leafnum - 1),huff);
		if(InerDlg->m_check)
		InerDlg->MyCtrl.SetPos(100);
	}
	else
	{
		fwrite(& only_one_char,1,1,huff);
		fwrite(& totalbits,4,1,huff);//not consider that only one char is in the file,and it's number is over 2147483647
		fwrite(&  only_c,1,1,huff);
		if(InerDlg->m_check)
		InerDlg->MyCtrl.SetPos(100);
	}
	fclose(source);
	fclose(huff);
}
#endif